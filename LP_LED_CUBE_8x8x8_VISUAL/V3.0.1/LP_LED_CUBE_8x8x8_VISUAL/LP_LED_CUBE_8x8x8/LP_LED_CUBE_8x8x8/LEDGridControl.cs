using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LP_LED_CUBE_8x8x8
{
    public partial class LEDGridControl : Control
    {
        private List<CheckBox> checks = new List<CheckBox>();

        [Bindable(true)]
        public byte[] CheckedBytes
        {
            get
            {
                byte[] bytestoreturn = new byte[8];
                BitArray bits = new BitArray(64);
                for (int x = 0; x < 64; x++)
                {
                    bits[x] = checks[x].Checked;
                }
                bits.CopyTo(bytestoreturn, 0);
                return bytestoreturn;
            }
            set
            {
                try
                {
                    BitArray bits = new BitArray(value);
                    for (int x = 0; x < 64; x++)
                    {
                        checks[x].Checked = bits[x];
                    }
                }
                catch (Exception ex)
                {
                    //Reset all
                    for (int x = 0; x < 64; x++)
                    {
                        checks[x].Checked = false;
                    }
                }
            }
        }

        public LEDGridControl()
        {
            InitializeComponent();

            for (int x = 0; x < 64; x++)
            {
                CheckBox check = new CheckBox();
                check.Width = 13;
                check.Height = 13;
                this.Controls.Add(check);
                this.checks.Add(check);
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            int zamiky = (Width - 12) / 7;
            int zamikx = (Height - 12) / 7;

            for (int x = 0; x < 8; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    checks[y * 8 + x].Location = new Point(y * zamiky, x * zamikx);
                }
            }
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            this.SuspendLayout();

            int zamiky = (Width - 12) / 7;
            int zamikx = (Height - 12) / 7;

            for (int x = 0; x < 8; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    checks[y * 8 + x].Location = new Point(y * zamiky, x * zamikx);
                }
            }

            this.PerformLayout();
            this.Refresh();
        }
    }
}
