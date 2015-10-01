using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace V400_DEVELOPER_TEST
{
    public partial class Form1 : Form
    {
        byte[,] cube = new byte[8, 8];

        public Form1()
        {
            InitializeComponent();
        }

        private void buttonSerialPortConnect_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen == false)
            {
                try
                {
                    if (comboBoxSerialPort.Items.Count > 0)
                    {
                        string portname = comboBoxSerialPort.SelectedItem.ToString();
                        serialPort1.PortName = portname;
                        try
                        {
                            serialPort1.Open();
                        }
                        catch (Exception el)
                        {
                            MessageBox.Show(el.ToString());
                            return;
                        }
                        buttonSerialPortConnect.Text = "Disconnect";
                        comboBoxSerialPort.Enabled = false;
                    }
                }
                catch (Exception b)
                {
                    MessageBox.Show(b.ToString());
                    comboBoxSerialPort.Enabled = true;
                    buttonSerialPortConnect.Text = "Connect";
                }
            }
            else
            {
                try
                {
                    try
                    {
                        serialPort1.Close();
                    }
                    catch (Exception el)
                    {
                        MessageBox.Show(el.ToString());
                        return;
                    }

                    buttonSerialPortConnect.Text = "Connect";
                    comboBoxSerialPort.Enabled = true;
                }
                catch (Exception b)
                {
                    MessageBox.Show(b.ToString());
                    buttonSerialPortConnect.Text = "Connect";
                    comboBoxSerialPort.Enabled = true;
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            timer1.Start();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            int count = System.IO.Ports.SerialPort.GetPortNames().Count();

            if (serialPort1.IsOpen == false && count != comboBoxSerialPort.Items.Count)
            {
                comboBoxSerialPort.Items.Clear();

                comboBoxSerialPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());

                if (comboBoxSerialPort.Items.Count > 0)
                {
                    comboBoxSerialPort.SelectedIndex = 0;
                    comboBoxSerialPort.Enabled = true;
                }
                else
                {
                    comboBoxSerialPort.Enabled = false;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
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

                serialPort1.Write(buffer, 0, buffer.Length);
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
