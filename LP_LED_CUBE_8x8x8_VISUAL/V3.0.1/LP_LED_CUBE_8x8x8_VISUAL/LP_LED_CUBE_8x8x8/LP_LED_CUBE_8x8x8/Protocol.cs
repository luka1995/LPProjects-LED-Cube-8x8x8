using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Collections;
using System.Threading;

namespace LP_LED_CUBE_8x8x8
{
    class Protocol
    {
        public static byte Protocol_start_byte1 = 0xEE;
        public static byte Protocol_start_byte2 = 0xEE;
        public static byte Protocol_start_byte3 = 0xCC;

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

        /******************************************************************
        ** UDP
        ******************************************************************/

        public enum UDPCheckWhich
        {
            none = 0,
            search_device = 0,
        }

        public static UDPCheckWhich UDPCheck(byte[] buffer, int length)
        {
            if (buffer[0] == Protocol_start_byte1 && buffer[1] == Protocol_start_byte2 && buffer[2] == Protocol_start_byte3)
            {
                if (CRC_Calculate(buffer, length - 1) == buffer[length - 1] && (((buffer[3] & 0x00FF) << 8) + buffer[4]) == length)
                {
                    switch (buffer[5])
                    {
                        case 0x00:
                            return UDPCheckWhich.search_device;
                    }
                }
            }

            return UDPCheckWhich.none;
        }

        public static bool UDPSend_SearchDevice(UdpClient socket, IPEndPoint endPoint, byte[] ipAddressBytes)
        {
            try
            {
                byte[] buffer = new byte[11];

                buffer[0] = Protocol_start_byte1;
                buffer[1] = Protocol_start_byte2;
                buffer[2] = Protocol_start_byte3;
                buffer[3] = (byte)(buffer.Length / 255);
                buffer[4] = (byte)(buffer.Length - (buffer[3] * 255));
                buffer[5] = 0x00; // Function
                buffer[6] = ipAddressBytes[0];
                buffer[7] = ipAddressBytes[1];
                buffer[8] = ipAddressBytes[2];
                buffer[9] = ipAddressBytes[3];
                buffer[buffer.Length - 1] = CRC_Calculate(buffer, buffer.Length - 1);

                socket.Send(buffer, buffer.Length, endPoint);

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }

        /******************************************************************
        ** TCP
        ******************************************************************/

        public enum TCPCheckWhich
        {
            none = 0,
        }

        public static TCPCheckWhich TCPCheck(byte[] buffer, int length)
        {
            if (buffer[0] == Protocol_start_byte1 && buffer[1] == Protocol_start_byte2 && buffer[2] == Protocol_start_byte3)
            {
                if (CRC_Calculate(buffer, length - 1) == buffer[length - 1] && (((buffer[3] & 0x00FF) << 8) + buffer[4]) == length)
                {
                    /*
                    switch (buffer[5])
                    {
                        case 0x01:
                            return TCPCheckWhich.uart_open_port;
                        case 0x02:
                            return TCPCheckWhich.uart_close_port;
                        case 0x03:
                            return TCPCheckWhich.uart_type_set;
                        case 0x04:
                            return TCPCheckWhich.uart_send_buffer;
                        case 0x05:
                            return TCPCheckWhich.uart_baud_rate_set;
                    }*/
                }
            }

            return TCPCheckWhich.none;
        }

        public static void TCPSend_Row_Set(TcpClient tcpSocket, int number, bool state)
        {
            try
            {
                NetworkStream clientStream = tcpSocket.GetStream();

                byte[] buffer = new byte[9];

                buffer[0] = Protocol.Protocol_start_byte1;
                buffer[1] = Protocol.Protocol_start_byte2;
                buffer[2] = Protocol.Protocol_start_byte3;
                buffer[3] = (byte)(buffer.Length / 255);
                buffer[4] = (byte)(buffer.Length - (buffer[3] * 255));
                buffer[5] = 0x12; // Function
                buffer[6] = (byte)number;
                buffer[7] = (byte)(state ? 0x01 : 0x00);
                buffer[buffer.Length - 1] = Protocol.CRC_Calculate(buffer, buffer.Length - 1);

                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();
            }
            catch (Exception)
            {

            }
        }

        public static void TCPSend_Rows_Set(TcpClient tcpSocket, byte rows)
        {
            try
            {
                NetworkStream clientStream = tcpSocket.GetStream();

                byte[] buffer = new byte[8];

                buffer[0] = Protocol.Protocol_start_byte1;
                buffer[1] = Protocol.Protocol_start_byte2;
                buffer[2] = Protocol.Protocol_start_byte3;
                buffer[3] = (byte)(buffer.Length / 255);
                buffer[4] = (byte)(buffer.Length - (buffer[3] * 255));
                buffer[5] = 0x13; // Function
                buffer[6] = (byte)rows;
                buffer[buffer.Length - 1] = Protocol.CRC_Calculate(buffer, buffer.Length - 1);

                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();
            }
            catch (Exception)
            {

            }
        }

        public static void TCPSend_Column_Set(TcpClient tcpSocket, int number, bool state)
        {
            try
            {
                NetworkStream clientStream = tcpSocket.GetStream();

                byte[] buffer = new byte[9];

                buffer[0] = Protocol.Protocol_start_byte1;
                buffer[1] = Protocol.Protocol_start_byte2;
                buffer[2] = Protocol.Protocol_start_byte3;
                buffer[3] = (byte)(buffer.Length / 255);
                buffer[4] = (byte)(buffer.Length - (buffer[3] * 255));
                buffer[5] = 0x14; // Function
                buffer[6] = (byte)number;
                buffer[7] = (byte)(state ? 0x01 : 0x00);
                buffer[buffer.Length - 1] = Protocol.CRC_Calculate(buffer, buffer.Length - 1);

                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();
            }
            catch (Exception)
            {

            }
        }

        public static void TCPSend_Columns_Set(TcpClient tcpSocket, byte[] columns)
        {
            try
            {
                NetworkStream clientStream = tcpSocket.GetStream();

                byte[] buffer = new byte[14];

                buffer[0] = Protocol.Protocol_start_byte1;
                buffer[1] = Protocol.Protocol_start_byte2;
                buffer[2] = Protocol.Protocol_start_byte3;
                buffer[3] = (byte)(buffer.Length / 255);
                buffer[4] = (byte)(buffer.Length - (buffer[3] * 255));
                buffer[5] = 0x15; // Function
                buffer[6] = columns[0];
                buffer[7] = columns[1];
                buffer[8] = columns[2];
                buffer[9] = columns[3];
                buffer[10] = columns[4];
                buffer[11] = columns[5];
                buffer[12] = columns[6];
                buffer[13] = columns[7];
                buffer[buffer.Length - 1] = Protocol.CRC_Calculate(buffer, buffer.Length - 1);

                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();
            }
            catch (Exception)
            {

            }
        }

        public static void TCPSend_Animation_Start(TcpClient tcpSocket, string animationName)
        {
            try
            {
                NetworkStream clientStream = tcpSocket.GetStream();

                byte[] buffer = new byte[7 + animationName.Length];

                buffer[0] = Protocol.Protocol_start_byte1;
                buffer[1] = Protocol.Protocol_start_byte2;
                buffer[2] = Protocol.Protocol_start_byte3;
                buffer[3] = (byte)(buffer.Length / 255);
                buffer[4] = (byte)(buffer.Length - (buffer[3] * 255));
                buffer[5] = 0x10;

                for (int i = 0; i < animationName.Length; i++)
                {
                    buffer[6 + i] = (byte)animationName[i];
                }

                buffer[buffer.Length - 1] = Protocol.CRC_Calculate(buffer, buffer.Length - 1);

                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();
            }
            catch (Exception)
            {

            }
        }

        public static void TCPSend_Animation_Stop(TcpClient tcpSocket)
        {
            try
            {
                NetworkStream clientStream = tcpSocket.GetStream();

                byte[] buffer = new byte[7];

                buffer[0] = Protocol.Protocol_start_byte1;
                buffer[1] = Protocol.Protocol_start_byte2;
                buffer[2] = Protocol.Protocol_start_byte3;
                buffer[3] = (byte)(buffer.Length / 255);
                buffer[4] = (byte)(buffer.Length - (buffer[3] * 255));
                buffer[5] = 0x11;
                buffer[buffer.Length - 1] = Protocol.CRC_Calculate(buffer, buffer.Length - 1);

                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();
            }
            catch (Exception)
            {

            }
        }
    }
}
