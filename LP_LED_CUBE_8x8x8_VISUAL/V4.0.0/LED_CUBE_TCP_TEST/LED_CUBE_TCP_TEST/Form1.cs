using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;

namespace LED_CUBE_TCP_TEST
{
    public partial class Form1 : Form
    {
        TcpClient tcpClient = new TcpClient();
        byte[,] cube = new byte[8, 8];

        public Form1()
        {
            InitializeComponent();
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            if (!tcpClient.Connected)
            {
                string ipString = textBoxIP.Text;

                IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(ipString), 14350);

                try
                {
                    tcpClient.Connect(serverEndPoint);

                    buttonConnect.Text = "Disconnect";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "TCP Connection Error");

                    buttonConnect.Text = "Connect";
                }
            }
            else
            {
                try
                {
                    tcpClient.Close();

                    buttonConnect.Text = "Connect";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "TCP Connection Error");

                    buttonConnect.Text = "Disconnect";
                }
            }
        }

        private void buttonSendFull_Click(object sender, EventArgs e)
        {
            if (tcpClient.Connected)
            {
                for (int layer = 0; layer < 8; layer++)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        cube[layer, i] = 0xFF;
                    }
                }

                NetworkStream clientStream = tcpClient.GetStream();

                byte[] buffer = new byte[71];

                buffer[0] = 0xEE;
                buffer[1] = 0xEE;
                buffer[2] = 0xCC;
                buffer[3] = (byte)(buffer.Length / 255);
                buffer[4] = (byte)(buffer.Length - (buffer[3] * 255));
                buffer[5] = 0x01; // Function

                for (int a = 0; a < 8; a++)
                {
                    for (int b = 0; b < 8; b++)
                    {
                        buffer[(a * b) + 6] = cube[a, b];
                    }
                }

                buffer[buffer.Length - 1] = CRC_Calculate(buffer, buffer.Length - 1);

                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();
            }
        }

        private void buttonSendClear_Click(object sender, EventArgs e)
        {
            if (tcpClient.Connected)
            {
                for (int layer = 0; layer < 8; layer++)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        cube[layer, i] = 0x00;
                    }
                }

                NetworkStream clientStream = tcpClient.GetStream();

                byte[] buffer = new byte[71];

                buffer[0] = 0xEE;
                buffer[1] = 0xEE;
                buffer[2] = 0xCC;
                buffer[3] = (byte)(buffer.Length / 255);
                buffer[4] = (byte)(buffer.Length - (buffer[3] * 255));
                buffer[5] = 0x01; // Function

                for (int a = 0; a < 8; a++)
                {
                    for (int b = 0; b < 8; b++)
                    {
                        buffer[(a * b) + 6] = cube[a, b];
                    }
                }

                buffer[buffer.Length - 1] = CRC_Calculate(buffer, buffer.Length - 1);

                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();
            }
        }

        /******************************************************************
        ** CRC Calculation
        ******************************************************************/

        private static byte CRC_Update(byte icrc, byte data)
        {
            byte i;

            icrc = (byte)(icrc ^ data);
            for (i = 0; i < 8; i++)
            {
                if ((icrc & 0x01) != 0)
                    icrc = (byte)((icrc >> 1) ^ 0x8C);
                else
                    icrc >>= 1;
            }

            return icrc;
        }

        public static byte CRC_Calculate(byte[] data, int len)
        {
            byte crc = 0x42;
            int i;

            for (i = 0; i < len; i++)
                crc = CRC_Update(crc, data[i]);
            return (crc);
        }
    }
}
