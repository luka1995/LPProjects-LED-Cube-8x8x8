using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
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

        private BindingList<LED_CUBE_Effect> AnimationList = new BindingList<LED_CUBE_Effect>();

        /******************************************************************
        ** Class methods
        ******************************************************************/

        public Form1()
        {
            InitializeComponent();

            lEDCUBEEffectBindingSource.DataSource = AnimationList;

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

                AddLog("Connect to device " + cbDevicesIP.SelectedItem.ToString());

                ftpClient = new FTPClient("ftp://" + cbDevicesIP.SelectedItem.ToString(), ftpUsername, ftpPassword);

                btnRefreshAnimationsList.Enabled = true;

                loadAnimationsList();

                textBoxNewAnimationName.Enabled = true;
                buttonUpload.Enabled = true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());

                ftpClient = null;

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

                AddLog("Disconnect from device " + cbDevicesIP.SelectedItem.ToString());

                ftpClient = null;

                clearComboBoxAnimationsList();

                cbAnimationsList.Enabled = false;
                btnRefreshAnimationsList.Enabled = false;
                cbAnimationsList.Enabled = false;
                buttonPlayAnimation.Enabled = false;
                buttonStopAnimation.Enabled = false;
                buttonDeleteAnimation.Enabled = false;

                textBoxNewAnimationName.Enabled = false;
                buttonUpload.Enabled = false;
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

                ftpClient = null;
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

            AddLog("Disconnect from device " + cbDevicesIP.SelectedItem.ToString());

            clearComboBoxAnimationsList();

            cbAnimationsList.Enabled = false;
            btnRefreshAnimationsList.Enabled = false;
            cbAnimationsList.Enabled = false;
            buttonPlayAnimation.Enabled = false;
            buttonStopAnimation.Enabled = false;
            buttonDeleteAnimation.Enabled = false;

            textBoxNewAnimationName.Enabled = false;
            buttonUpload.Enabled = false;
        }

        public void TCPSocketClose()
        {
            if (tcpSocket != null)
            {
                tcpSocket.Close();
                tcpSocket = null;

                ftpClient = null;
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
            if (ftpClient != null)
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
                    buttonPlayAnimation.Enabled = true;
                    buttonStopAnimation.Enabled = true;
                    buttonDeleteAnimation.Enabled = true;
                }
                else
                {
                    cbAnimationsList.Enabled = false;
                    buttonPlayAnimation.Enabled = false;
                    buttonStopAnimation.Enabled = false;
                    buttonDeleteAnimation.Enabled = false;
                }

                AddLog("Refresh animations list");
            }
        }

        private void clearComboBoxAnimationsList()
        {
            cbAnimationsList.Items.Clear();
        }

        private void buttonPlayAnimation_Click(object sender, EventArgs e)
        {
            Protocol.TCPSend_Animation_Start(tcpSocket, cbAnimationsList.SelectedItem.ToString() + animationFileExtension);
        }

        private void buttonStopAnimation_Click(object sender, EventArgs e)
        {
            Protocol.TCPSend_Animation_Stop(tcpSocket);
        }

        private void buttonFileSave_Click(object sender, EventArgs e)
        {
            if (AnimationList.Count > 0)
            {
                saveFileDialog.ShowDialog();
            }
            else
            {
                MessageBox.Show("Animation is empty", "Error");
            }
        }

        private void saveFileDialog_FileOk(object sender, CancelEventArgs e)
        {
            try
            {
                BinaryWriter fileStream = new BinaryWriter(new FileStream(saveFileDialog.FileName + ".ani", System.IO.FileMode.Create, System.IO.FileAccess.Write));

                for (int i = 0; i < AnimationList.Count; i++)
                {
                    fileStream.Write(AnimationList[i].Bytes());
                }

                fileStream.Close();
            }
            catch (IOException el)
            {
                Console.WriteLine(el);
            }
        }

        private void dataGridViewAnimation_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            if (e.ColumnIndex == 0)
            {
                e.Value = e.RowIndex+1;
            }
        }

        private void buttonNewEffect_Click(object sender, EventArgs e)
        {
            lEDCUBEEffectBindingSource.AddNew();
        }

        private void buttonDeleteEffect_Click(object sender, EventArgs e)
        {
            DialogResult dialogResult = MessageBox.Show("Are you sure you want to delete?", "Warning",  MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                if (lEDCUBEEffectBindingSource.Current != null)
                    lEDCUBEEffectBindingSource.Remove(lEDCUBEEffectBindingSource.Current);
            }
        }

        private void buttonDeleteAllEffect_Click(object sender, EventArgs e)
        {
            DialogResult dialogResult = MessageBox.Show("Are you sure you want to delete all?", "Warning", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                if (lEDCUBEEffectBindingSource.Current != null)
                    AnimationList.Clear();
            }
        }

        private void buttonLoadAnimationFile_Click(object sender, EventArgs e)
        {
            openFileDialog.ShowDialog();
        }

        private void openFileDialog_FileOk(object sender, CancelEventArgs e)
        {
            byte[] fileBytes = File.ReadAllBytes(openFileDialog.FileName);

            AnimationList.Clear();

            int count = (fileBytes.Length / LED_CUBE_Effect.Size());

            if (count > 0)
            {
                for (int i = 0; i < count; i++)
                {
                    byte[] bytes = new byte[31];

                    Array.Copy(fileBytes, (LED_CUBE_Effect.Size() * i), bytes, 0, LED_CUBE_Effect.Size());

                    LED_CUBE_Effect effect = new LED_CUBE_Effect(bytes);

                    AnimationList.Add(effect);
                }

                textBoxNewAnimationName.Text = Path.GetFileName(openFileDialog.FileName.ToString().Replace(animationFileExtension, ""));
            }
            else
            {
                MessageBox.Show("Animation is empty", "Error");
            }
        }

        private void buttonCopyEffect_Click(object sender, EventArgs e)
        {
            if (dataGridViewAnimation.SelectedRows.Count > 0)
            {
                int selectedIndex = dataGridViewAnimation.SelectedRows[0].Index;

                //AnimationList.Add((LED_CUBE_Effect)AnimationList[selectedIndex].Clone());

                //dataGridViewAnimation.Rows[AnimationList.Count - 1].Selected = true;
                //lEDCUBEEffectBindingSource.AddNew();

                lEDCUBEEffectBindingSource.AddNew();

                AnimationList[AnimationList.Count - 1] = (LED_CUBE_Effect)AnimationList[selectedIndex].Clone();

                //lEDCUBEEffectBindingSource.ResetItem(AnimationList.Count - 1);
            }
        }

        private void buttonUpload_Click(object sender, EventArgs e)
        {
            if (ftpClient != null)
            {
                if (AnimationList.Count > 0)
                {
                    if (textBoxNewAnimationName.Text.Length > 0)
                    {
                        string fileName = textBoxNewAnimationName.Text + animationFileExtension;

                        byte[] buffer = new byte[AnimationList.Count * LED_CUBE_Effect.Size()];

                        for (int i = 0; i < AnimationList.Count; i++)
                        {
                            for (int j = 0; j < LED_CUBE_Effect.Size(); j++)
                            {
                                buffer[(i * LED_CUBE_Effect.Size()) + j] = AnimationList[i].Bytes()[j];
                            }
                        }

                        ftpClient.uploadBuffer(fileName, buffer);

                        loadAnimationsList();
                    }
                    else
                    {
                        MessageBox.Show("Enter animation name", "Error");
                    }
                }
                else
                {
                    MessageBox.Show("Animation is empty", "Error");
                }
            }
        }

        private void buttonDeleteAnimation_Click(object sender, EventArgs e)
        {
            if (ftpClient != null && cbAnimationsList.SelectedItem != null)
            {
                ftpClient.delete(cbAnimationsList.SelectedItem.ToString() + animationFileExtension);

                loadAnimationsList();
            }
        }

        private void buttonSelectAllColumns_Click(object sender, EventArgs e)
        {
            if (dataGridViewAnimation.SelectedRows.Count > 0)
            {
                LED_CUBE_Effect effect = AnimationList[dataGridViewAnimation.SelectedRows[0].Index];

                Byte[] data = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
                effect.columns = data;

                ledGridControl.CheckedBytes = data;
            }
        }

        private void buttonDeselectAllColumns_Click(object sender, EventArgs e)
        {
            if (dataGridViewAnimation.SelectedRows.Count > 0)
            {
                LED_CUBE_Effect effect = AnimationList[dataGridViewAnimation.SelectedRows[0].Index];

                Byte[] data = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
                effect.columns = data;

                ledGridControl.CheckedBytes = data;
            }
        }

        private void buttonAllRowsON_Click(object sender, EventArgs e)
        {
            if (dataGridViewAnimation.SelectedRows.Count > 0)
            {
                LED_CUBE_Effect effect = AnimationList[dataGridViewAnimation.SelectedRows[0].Index];

                effect.rows = 0xFF;
                effect.chk1 = true;
                effect.chk2 = true;
                effect.chk3 = true;
                effect.chk4 = true;
                effect.chk5 = true;
                effect.chk6 = true;
                effect.chk7 = true;
                effect.chk8 = true;
            }
        }

        private void buttonAllRowsOFF_Click(object sender, EventArgs e)
        {
            if (dataGridViewAnimation.SelectedRows.Count > 0)
            {
                LED_CUBE_Effect effect = AnimationList[dataGridViewAnimation.SelectedRows[0].Index];

                effect.rows = 0x00;
                effect.chk1 = false;
                effect.chk2 = false;
                effect.chk3 = false;
                effect.chk4 = false;
                effect.chk5 = false;
                effect.chk6 = false;
                effect.chk7 = false;
                effect.chk8 = false;
            }
        }

        private void buttonAppendFile_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            byte[] fileBytes = File.ReadAllBytes(openFileDialog1.FileName);

            int count = (fileBytes.Length / LED_CUBE_Effect.Size());

            if (count > 0)
            {
                for (int i = 0; i < count; i++)
                {
                    byte[] bytes = new byte[31];

                    Array.Copy(fileBytes, (LED_CUBE_Effect.Size() * i), bytes, 0, LED_CUBE_Effect.Size());

                    LED_CUBE_Effect effect = new LED_CUBE_Effect(bytes);

                    AnimationList.Add(effect);
                }
            }
            else
            {
                MessageBox.Show("Animation is empty", "Error");
            }
        }
    }
}
