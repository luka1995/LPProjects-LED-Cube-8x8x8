using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LP_LED_CUBE_8x8x8
{
    public partial class Form1 : Form
    {
        /******************************************************************
        ** Configuration
        ******************************************************************/

        int UDPPort = 10023;
        int TCPPort = 10023;
        string UDPBroadcastIP = "255.255.255.255";
        int UDPBroadcastScaningTime = 4000; // In seconds 

        string ftpUsername = "manufacturer";
        string ftpPassword = "manufacturer";

        string animationFileExtension = ".ani";

        /******************************************************************
        ** Variables
        ******************************************************************/

        public delegate void Delegate();

        public UdpClient udpSocket;
        public IPEndPoint udpBroadcastEndPoint;
        public TcpClient tcpSocket;
        public Thread tcpSocketThread;

        private FTPClient ftpClient;

        /******************************************************************
        ** Class methods
        ******************************************************************/

        public Form1()
        {
            InitializeComponent();

            //
            // UDP Socket -Broadcast 
            //
            udpSocket = new UdpClient(UDPPort);
            udpBroadcastEndPoint = new IPEndPoint(IPAddress.Parse(UDPBroadcastIP), UDPPort);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ScanDevicesStart();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //
            // UDP Socket close
            //
            UDPSocketClose();

            //
            //
            // TCP Socket close
            TCPSocketClose();
        }

        private void AddLog(string Str)
        {
            editLog.AppendText(DateTime.Now.ToString("T") + " - " + Str + "\r\n");
            editLog.Select(editLog.TextLength, 0);
        }

        public IPAddress getLocalIPAddress()
        {
            IPHostEntry host;

            host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (IPAddress ip in host.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    return ip;
                }
            }
            return null;
        }

        /******************************************************************
        ** Scanning Devices UDP - Connect/Disconnect
        ******************************************************************/

        private void btnScanDevices_Click(object sender, EventArgs e)
        {
            ScanDevicesStart();
        }

        int timerUDPBroadcastCount = 0;

        public void UDPSocketClose()
        {
            if (udpSocket != null)
            {
                udpSocket.Close();
                udpSocket = null;
            }
        }

        public void ScanDevicesStart()
        {
            timerUDPBroadcastCount = 0;

            cbDevicesIP.Items.Clear();
            btnScanDevices.Enabled = true;
            cbDevicesIP.Enabled = false;
            btnConnectDevice.Enabled = false;

            timerUDPBroadcast.Enabled = true;
            timerUDPBroadcast.Start();

            Protocol.UDPSend_SearchDevice(udpSocket, udpBroadcastEndPoint, getLocalIPAddress().GetAddressBytes());

            AddLog("Searching for devices");
        }

        private void timerUDPBroadcast_Tick(object sender, EventArgs e)
        {
            Invoke(new Delegate(delegate()
            {
                try
                {
                    if (udpSocket.Available > 0)
                    {
                        IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Any, UDPPort);

                        byte[] receiveBytes = udpSocket.Receive(ref RemoteIpEndPoint);

                        IPAddress remoteIP = RemoteIpEndPoint.Address;

                        if (!remoteIP.Equals(getLocalIPAddress()))
                        {
                            Protocol.UDPCheckWhich whichData = Protocol.UDPCheck(receiveBytes, receiveBytes.Length);

                            switch (whichData)
                            {
                                case Protocol.UDPCheckWhich.search_device:
                                    string ipAddress = String.Format("{0:###}.{1:###}.{2:###}.{3:###}", remoteIP.GetAddressBytes()[0], remoteIP.GetAddressBytes()[1], remoteIP.GetAddressBytes()[2], remoteIP.GetAddressBytes()[3]);

                                    cbDevicesIP.Items.Add(ipAddress);
                                    cbDevicesIP.SelectedIndex = 0;
                                    cbDevicesIP.Enabled = true;

                                    btnConnectDevice.Enabled = true;
                                    break;
                                default:

                                    break;
                            }
                        }
                    }
                }
                catch (Exception)
                {

                }

                //
                // Timer check
                //
                timerUDPBroadcastCount += timerUDPBroadcast.Interval;

                if (timerUDPBroadcastCount >= UDPBroadcastScaningTime)
                {
                    timerUDPBroadcast.Stop();
                    timerUDPBroadcast.Enabled = false;
                }
            }));
        }

        /******************************************************************
        ** TCP Socket - Connect/Disconnect
        ******************************************************************/

        private void btnConnectDevice_Click(object sender, EventArgs e)
        {
            timerUDPBroadcast.Stop();
            timerUDPBroadcast.Enabled = false;

            if (btnConnectDevice.Text.ToString() == "Connect")
            {
                TCPConnectDevice();
            }
            else
            {
                TCPDisconnectDevice();
            }
        }

        public void TCPConnectDevice()
        {
            try
            {
                string ipAddress = cbDevicesIP.Items[cbDevicesIP.SelectedIndex].ToString();

                IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse(ipAddress), TCPPort);
                tcpSocket = new TcpClient();
                tcpSocket.Connect(endPoint);

                tcpSocketThread = new Thread(new ParameterizedThreadStart(TCPSocketHandler));
                tcpSocketThread.IsBackground = true;
                tcpSocketThread.Start(tcpSocket);

                btnConnectDevice.Text = "Disconnect";
                cbDevicesIP.Enabled = false;
                btnScanDevices.Enabled = false;

                AddLog("Connect to device");

                ftpClient = new FTPClient("ftp://" + cbDevicesIP.SelectedItem.ToString(), ftpUsername, ftpPassword);

                loadAnimationsList();

                cbAnimationsList.Enabled = true;
                btnRefreshAnimationsList.Enabled = true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());

                btnConnectDevice.Text = "Connect";
                btnScanDevices.Enabled = true;
                if (cbDevicesIP.Items.Count > 0)
                {
                    cbDevicesIP.Enabled = true;
                }
                else
                {
                    cbDevicesIP.Enabled = false;
                }

                AddLog("Disconnect from device");

                ftpClient = null;

                clearComboBoxAnimationsList();

                cbAnimationsList.Enabled = false;
                btnRefreshAnimationsList.Enabled = false;
            }
        }

        public void TCPDisconnectDevice()
        {
            try
            {
                tcpSocket.Close();
                tcpSocket = null;

                tcpSocketThread.Abort();
                tcpSocketThread = null;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }

            btnConnectDevice.Text = "Connect";
            btnScanDevices.Enabled = true;
            if (cbDevicesIP.Items.Count > 0)
            {
                cbDevicesIP.Enabled = true;
            }
            else
            {
                cbDevicesIP.Enabled = false;
            }

            AddLog("Disconnect from device");

            clearComboBoxAnimationsList();

            cbAnimationsList.Enabled = false;
            btnRefreshAnimationsList.Enabled = false;
        }

        public void TCPSocketClose()
        {
            if (tcpSocket != null)
            {
                tcpSocket.Close();
                tcpSocket = null;
            }
        }

        private void TCPSocketHandler(object client)
        {
            NetworkStream clientStream = tcpSocket.GetStream();

            int length = 0;
            byte[] buffer = new byte[200];

            while (true)
            {
                length = 0;

                try
                {
                    //blocks until a client sends a message
                    length = clientStream.Read(buffer, 0, buffer.Length);

                    Protocol.TCPCheckWhich whichData = Protocol.TCPCheck(buffer, length);


                }
                catch
                {
                    length = 0;
                }

                if (length == 0)
                {
                    //Client has disconnected

                    Invoke(new Delegate(delegate()
                    {
                        TCPDisconnectDevice();
                    }));

                    break;
                }
            }
        }

        private void buttonRowSet_Click(object sender, EventArgs e)
        {
            Protocol.TCPSend_Row_Set(tcpSocket, (int)numericUpDownRow.Value, checkBoxRowState.Checked);
        }

        private void buttonRowsSet_Click(object sender, EventArgs e)
        {
            byte rows = 0x00;

            if (checkBoxRow1.Checked) rows |= 0x01;
            if (checkBoxRow2.Checked) rows |= 0x02;
            if (checkBoxRow3.Checked) rows |= 0x04;
            if (checkBoxRow4.Checked) rows |= 0x08;
            if (checkBoxRow5.Checked) rows |= 0x10;
            if (checkBoxRow6.Checked) rows |= 0x20;
            if (checkBoxRow7.Checked) rows |= 0x40;
            if (checkBoxRow8.Checked) rows |= 0x80;

            Protocol.TCPSend_Rows_Set(tcpSocket, rows);
        }

        private void buttonRowsRead_Click(object sender, EventArgs e)
        {

        }

        private void buttonColumnSet_Click(object sender, EventArgs e)
        {
            Protocol.TCPSend_Column_Set(tcpSocket, (int)numericUpDownColumn.Value, checkBoxColumnState.Checked);
        }

        private void buttonColumnsSet_Click(object sender, EventArgs e)
        {
            Protocol.TCPSend_Columns_Set(tcpSocket, ledGridControl.CheckedBytes);
        }

        /******************************************************************
        ** Animations
        ******************************************************************/

        private string[] getAnimationsList(FTPClient ftp)
        {
            if (ftp != null)
            {
                List<string> list = new List<string>();

                string[] filesList = ftpClient.directoryListSimple("");

                foreach (string file in filesList)
                {
                    if (file.Contains(animationFileExtension))
                    {
                        list.Add(file.Replace(animationFileExtension, ""));
                    }
                }

                return list.ToArray();
            }

            return null;
        }

        private void btnRefreshAnimationsList_Click(object sender, EventArgs e)
        {
            if (tcpSocket.Connected)
            {
                loadAnimationsList();
            }
        }

        private void loadAnimationsList()
        {
            clearComboBoxAnimationsList();

            if (ftpClient != null)
            {
                string[] animationsList = getAnimationsList(ftpClient);

                cbAnimationsList.Items.AddRange(animationsList);

                if (cbAnimationsList.Items.Count > 0)
                {
                    cbAnimationsList.SelectedIndex = 0;

                    cbAnimationsList.Enabled = true;
                }
                else
                {
                    cbAnimationsList.Enabled = false;
                }

                AddLog("Refresh animations list");
            }
        }

        private void clearComboBoxAnimationsList()
        {
            cbAnimationsList.Items.Clear();
        }
    }
}
