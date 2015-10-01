namespace LED_CUBE_TCP_TEST
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonConnect = new System.Windows.Forms.Button();
            this.textBoxIP = new System.Windows.Forms.TextBox();
            this.buttonSendFull = new System.Windows.Forms.Button();
            this.buttonSendClear = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(39, 85);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(242, 59);
            this.buttonConnect.TabIndex = 0;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // textBoxIP
            // 
            this.textBoxIP.Location = new System.Drawing.Point(39, 30);
            this.textBoxIP.Name = "textBoxIP";
            this.textBoxIP.Size = new System.Drawing.Size(242, 31);
            this.textBoxIP.TabIndex = 1;
            this.textBoxIP.Text = "192.168.2.100";
            // 
            // buttonSendFull
            // 
            this.buttonSendFull.Location = new System.Drawing.Point(225, 312);
            this.buttonSendFull.Name = "buttonSendFull";
            this.buttonSendFull.Size = new System.Drawing.Size(184, 49);
            this.buttonSendFull.TabIndex = 2;
            this.buttonSendFull.Text = "Full";
            this.buttonSendFull.UseVisualStyleBackColor = true;
            this.buttonSendFull.Click += new System.EventHandler(this.buttonSendFull_Click);
            // 
            // buttonSendClear
            // 
            this.buttonSendClear.Location = new System.Drawing.Point(424, 312);
            this.buttonSendClear.Name = "buttonSendClear";
            this.buttonSendClear.Size = new System.Drawing.Size(184, 49);
            this.buttonSendClear.TabIndex = 3;
            this.buttonSendClear.Text = "Clear";
            this.buttonSendClear.UseVisualStyleBackColor = true;
            this.buttonSendClear.Click += new System.EventHandler(this.buttonSendClear_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(829, 524);
            this.Controls.Add(this.buttonSendClear);
            this.Controls.Add(this.buttonSendFull);
            this.Controls.Add(this.textBoxIP);
            this.Controls.Add(this.buttonConnect);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.TextBox textBoxIP;
        private System.Windows.Forms.Button buttonSendFull;
        private System.Windows.Forms.Button buttonSendClear;
    }
}

