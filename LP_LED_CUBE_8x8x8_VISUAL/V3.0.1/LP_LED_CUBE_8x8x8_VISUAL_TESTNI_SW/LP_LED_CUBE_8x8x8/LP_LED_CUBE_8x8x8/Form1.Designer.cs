namespace LP_LED_CUBE_8x8x8
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
            this.components = new System.ComponentModel.Container();
            this.btnScanDevices = new System.Windows.Forms.Button();
            this.cbDevicesIP = new System.Windows.Forms.ComboBox();
            this.btnConnectDevice = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.editLog = new System.Windows.Forms.TextBox();
            this.timerUDPBroadcast = new System.Windows.Forms.Timer(this.components);
            this.buttonRowSet = new System.Windows.Forms.Button();
            this.numericUpDownRow = new System.Windows.Forms.NumericUpDown();
            this.checkBoxRowState = new System.Windows.Forms.CheckBox();
            this.buttonRowsSet = new System.Windows.Forms.Button();
            this.checkBoxRow1 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow2 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow3 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow6 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow5 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow4 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow8 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow7 = new System.Windows.Forms.CheckBox();
            this.buttonRowsRead = new System.Windows.Forms.Button();
            this.checkBoxColumnState = new System.Windows.Forms.CheckBox();
            this.numericUpDownColumn = new System.Windows.Forms.NumericUpDown();
            this.buttonColumnSet = new System.Windows.Forms.Button();
            this.buttonColumnsSet = new System.Windows.Forms.Button();
            this.ledGridControl = new LP_LED_CUBE_8x8x8.LEDGridControl();
            this.cbAnimationsList = new System.Windows.Forms.ComboBox();
            this.btnRefreshAnimationsList = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownRow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownColumn)).BeginInit();
            this.SuspendLayout();
            // 
            // btnScanDevices
            // 
            this.btnScanDevices.Location = new System.Drawing.Point(14, 12);
            this.btnScanDevices.Name = "btnScanDevices";
            this.btnScanDevices.Size = new System.Drawing.Size(75, 22);
            this.btnScanDevices.TabIndex = 38;
            this.btnScanDevices.Text = "Scan";
            this.btnScanDevices.Click += new System.EventHandler(this.btnScanDevices_Click);
            // 
            // cbDevicesIP
            // 
            this.cbDevicesIP.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDevicesIP.Enabled = false;
            this.cbDevicesIP.FormattingEnabled = true;
            this.cbDevicesIP.Location = new System.Drawing.Point(100, 12);
            this.cbDevicesIP.MaxDropDownItems = 100;
            this.cbDevicesIP.Name = "cbDevicesIP";
            this.cbDevicesIP.Size = new System.Drawing.Size(119, 21);
            this.cbDevicesIP.TabIndex = 36;
            // 
            // btnConnectDevice
            // 
            this.btnConnectDevice.Enabled = false;
            this.btnConnectDevice.Location = new System.Drawing.Point(230, 12);
            this.btnConnectDevice.Name = "btnConnectDevice";
            this.btnConnectDevice.Size = new System.Drawing.Size(75, 22);
            this.btnConnectDevice.TabIndex = 37;
            this.btnConnectDevice.Text = "Connect";
            this.btnConnectDevice.Click += new System.EventHandler(this.btnConnectDevice_Click);
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(14, 441);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(106, 19);
            this.label4.TabIndex = 40;
            this.label4.Text = "Log data";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // editLog
            // 
            this.editLog.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editLog.Location = new System.Drawing.Point(14, 464);
            this.editLog.Multiline = true;
            this.editLog.Name = "editLog";
            this.editLog.ReadOnly = true;
            this.editLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.editLog.Size = new System.Drawing.Size(607, 56);
            this.editLog.TabIndex = 39;
            // 
            // timerUDPBroadcast
            // 
            this.timerUDPBroadcast.Tick += new System.EventHandler(this.timerUDPBroadcast_Tick);
            // 
            // buttonRowSet
            // 
            this.buttonRowSet.Location = new System.Drawing.Point(17, 111);
            this.buttonRowSet.Name = "buttonRowSet";
            this.buttonRowSet.Size = new System.Drawing.Size(75, 23);
            this.buttonRowSet.TabIndex = 42;
            this.buttonRowSet.Text = "Row Set";
            this.buttonRowSet.UseVisualStyleBackColor = true;
            this.buttonRowSet.Click += new System.EventHandler(this.buttonRowSet_Click);
            // 
            // numericUpDownRow
            // 
            this.numericUpDownRow.Location = new System.Drawing.Point(17, 85);
            this.numericUpDownRow.Maximum = new decimal(new int[] {
            7,
            0,
            0,
            0});
            this.numericUpDownRow.Name = "numericUpDownRow";
            this.numericUpDownRow.Size = new System.Drawing.Size(66, 20);
            this.numericUpDownRow.TabIndex = 43;
            // 
            // checkBoxRowState
            // 
            this.checkBoxRowState.AutoSize = true;
            this.checkBoxRowState.Checked = true;
            this.checkBoxRowState.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRowState.Location = new System.Drawing.Point(89, 86);
            this.checkBoxRowState.Name = "checkBoxRowState";
            this.checkBoxRowState.Size = new System.Drawing.Size(76, 17);
            this.checkBoxRowState.TabIndex = 44;
            this.checkBoxRowState.Text = "Row State";
            this.checkBoxRowState.UseVisualStyleBackColor = true;
            // 
            // buttonRowsSet
            // 
            this.buttonRowsSet.Location = new System.Drawing.Point(17, 370);
            this.buttonRowsSet.Name = "buttonRowsSet";
            this.buttonRowsSet.Size = new System.Drawing.Size(75, 23);
            this.buttonRowsSet.TabIndex = 45;
            this.buttonRowsSet.Text = "Rows Set";
            this.buttonRowsSet.UseVisualStyleBackColor = true;
            this.buttonRowsSet.Click += new System.EventHandler(this.buttonRowsSet_Click);
            // 
            // checkBoxRow1
            // 
            this.checkBoxRow1.AutoSize = true;
            this.checkBoxRow1.Checked = true;
            this.checkBoxRow1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRow1.Location = new System.Drawing.Point(17, 188);
            this.checkBoxRow1.Name = "checkBoxRow1";
            this.checkBoxRow1.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow1.TabIndex = 46;
            this.checkBoxRow1.Text = "Row 1";
            this.checkBoxRow1.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow2
            // 
            this.checkBoxRow2.AutoSize = true;
            this.checkBoxRow2.Checked = true;
            this.checkBoxRow2.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRow2.Location = new System.Drawing.Point(17, 211);
            this.checkBoxRow2.Name = "checkBoxRow2";
            this.checkBoxRow2.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow2.TabIndex = 47;
            this.checkBoxRow2.Text = "Row 2";
            this.checkBoxRow2.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow3
            // 
            this.checkBoxRow3.AutoSize = true;
            this.checkBoxRow3.Checked = true;
            this.checkBoxRow3.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRow3.Location = new System.Drawing.Point(17, 234);
            this.checkBoxRow3.Name = "checkBoxRow3";
            this.checkBoxRow3.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow3.TabIndex = 48;
            this.checkBoxRow3.Text = "Row 3";
            this.checkBoxRow3.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow6
            // 
            this.checkBoxRow6.AutoSize = true;
            this.checkBoxRow6.Checked = true;
            this.checkBoxRow6.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRow6.Location = new System.Drawing.Point(17, 301);
            this.checkBoxRow6.Name = "checkBoxRow6";
            this.checkBoxRow6.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow6.TabIndex = 51;
            this.checkBoxRow6.Text = "Row 6";
            this.checkBoxRow6.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow5
            // 
            this.checkBoxRow5.AutoSize = true;
            this.checkBoxRow5.Checked = true;
            this.checkBoxRow5.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRow5.Location = new System.Drawing.Point(17, 278);
            this.checkBoxRow5.Name = "checkBoxRow5";
            this.checkBoxRow5.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow5.TabIndex = 50;
            this.checkBoxRow5.Text = "Row 5";
            this.checkBoxRow5.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow4
            // 
            this.checkBoxRow4.AutoSize = true;
            this.checkBoxRow4.Checked = true;
            this.checkBoxRow4.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRow4.Location = new System.Drawing.Point(17, 255);
            this.checkBoxRow4.Name = "checkBoxRow4";
            this.checkBoxRow4.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow4.TabIndex = 49;
            this.checkBoxRow4.Text = "Row 4";
            this.checkBoxRow4.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow8
            // 
            this.checkBoxRow8.AutoSize = true;
            this.checkBoxRow8.Checked = true;
            this.checkBoxRow8.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRow8.Location = new System.Drawing.Point(17, 347);
            this.checkBoxRow8.Name = "checkBoxRow8";
            this.checkBoxRow8.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow8.TabIndex = 53;
            this.checkBoxRow8.Text = "Row 8";
            this.checkBoxRow8.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow7
            // 
            this.checkBoxRow7.AutoSize = true;
            this.checkBoxRow7.Checked = true;
            this.checkBoxRow7.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRow7.Location = new System.Drawing.Point(17, 324);
            this.checkBoxRow7.Name = "checkBoxRow7";
            this.checkBoxRow7.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow7.TabIndex = 52;
            this.checkBoxRow7.Text = "Row 7";
            this.checkBoxRow7.UseVisualStyleBackColor = true;
            // 
            // buttonRowsRead
            // 
            this.buttonRowsRead.Location = new System.Drawing.Point(17, 399);
            this.buttonRowsRead.Name = "buttonRowsRead";
            this.buttonRowsRead.Size = new System.Drawing.Size(75, 23);
            this.buttonRowsRead.TabIndex = 54;
            this.buttonRowsRead.Text = "Rows Read";
            this.buttonRowsRead.UseVisualStyleBackColor = true;
            this.buttonRowsRead.Click += new System.EventHandler(this.buttonRowsRead_Click);
            // 
            // checkBoxColumnState
            // 
            this.checkBoxColumnState.AutoSize = true;
            this.checkBoxColumnState.Checked = true;
            this.checkBoxColumnState.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxColumnState.Location = new System.Drawing.Point(339, 84);
            this.checkBoxColumnState.Name = "checkBoxColumnState";
            this.checkBoxColumnState.Size = new System.Drawing.Size(89, 17);
            this.checkBoxColumnState.TabIndex = 57;
            this.checkBoxColumnState.Text = "Column State";
            this.checkBoxColumnState.UseVisualStyleBackColor = true;
            // 
            // numericUpDownColumn
            // 
            this.numericUpDownColumn.Location = new System.Drawing.Point(267, 83);
            this.numericUpDownColumn.Maximum = new decimal(new int[] {
            63,
            0,
            0,
            0});
            this.numericUpDownColumn.Name = "numericUpDownColumn";
            this.numericUpDownColumn.Size = new System.Drawing.Size(66, 20);
            this.numericUpDownColumn.TabIndex = 56;
            // 
            // buttonColumnSet
            // 
            this.buttonColumnSet.Location = new System.Drawing.Point(267, 109);
            this.buttonColumnSet.Name = "buttonColumnSet";
            this.buttonColumnSet.Size = new System.Drawing.Size(75, 23);
            this.buttonColumnSet.TabIndex = 55;
            this.buttonColumnSet.Text = "Column Set";
            this.buttonColumnSet.UseVisualStyleBackColor = true;
            this.buttonColumnSet.Click += new System.EventHandler(this.buttonColumnSet_Click);
            // 
            // buttonColumnsSet
            // 
            this.buttonColumnsSet.Location = new System.Drawing.Point(258, 408);
            this.buttonColumnsSet.Name = "buttonColumnsSet";
            this.buttonColumnsSet.Size = new System.Drawing.Size(75, 23);
            this.buttonColumnsSet.TabIndex = 59;
            this.buttonColumnsSet.Text = "Columns Set";
            this.buttonColumnsSet.UseVisualStyleBackColor = true;
            this.buttonColumnsSet.Click += new System.EventHandler(this.buttonColumnsSet_Click);
            // 
            // ledGridControl
            // 
            this.ledGridControl.CheckedBytes = new byte[] {
        ((byte)(255)),
        ((byte)(255)),
        ((byte)(255)),
        ((byte)(255)),
        ((byte)(255)),
        ((byte)(255)),
        ((byte)(255)),
        ((byte)(255))};
            this.ledGridControl.Location = new System.Drawing.Point(267, 157);
            this.ledGridControl.Name = "ledGridControl";
            this.ledGridControl.Size = new System.Drawing.Size(288, 245);
            this.ledGridControl.TabIndex = 58;
            this.ledGridControl.Text = "ledGridControl";
            // 
            // cbAnimationsList
            // 
            this.cbAnimationsList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbAnimationsList.Enabled = false;
            this.cbAnimationsList.FormattingEnabled = true;
            this.cbAnimationsList.Location = new System.Drawing.Point(100, 39);
            this.cbAnimationsList.Name = "cbAnimationsList";
            this.cbAnimationsList.Size = new System.Drawing.Size(119, 21);
            this.cbAnimationsList.TabIndex = 61;
            // 
            // btnRefreshAnimationsList
            // 
            this.btnRefreshAnimationsList.Enabled = false;
            this.btnRefreshAnimationsList.Location = new System.Drawing.Point(14, 38);
            this.btnRefreshAnimationsList.Name = "btnRefreshAnimationsList";
            this.btnRefreshAnimationsList.Size = new System.Drawing.Size(75, 23);
            this.btnRefreshAnimationsList.TabIndex = 60;
            this.btnRefreshAnimationsList.Text = "Refresh List";
            this.btnRefreshAnimationsList.UseVisualStyleBackColor = true;
            this.btnRefreshAnimationsList.Click += new System.EventHandler(this.btnRefreshAnimationsList_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(633, 532);
            this.Controls.Add(this.cbAnimationsList);
            this.Controls.Add(this.btnRefreshAnimationsList);
            this.Controls.Add(this.buttonColumnsSet);
            this.Controls.Add(this.ledGridControl);
            this.Controls.Add(this.checkBoxColumnState);
            this.Controls.Add(this.numericUpDownColumn);
            this.Controls.Add(this.buttonColumnSet);
            this.Controls.Add(this.buttonRowsRead);
            this.Controls.Add(this.checkBoxRow8);
            this.Controls.Add(this.checkBoxRow7);
            this.Controls.Add(this.checkBoxRow6);
            this.Controls.Add(this.checkBoxRow5);
            this.Controls.Add(this.checkBoxRow4);
            this.Controls.Add(this.checkBoxRow3);
            this.Controls.Add(this.checkBoxRow2);
            this.Controls.Add(this.checkBoxRow1);
            this.Controls.Add(this.buttonRowsSet);
            this.Controls.Add(this.checkBoxRowState);
            this.Controls.Add(this.numericUpDownRow);
            this.Controls.Add(this.buttonRowSet);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.editLog);
            this.Controls.Add(this.btnScanDevices);
            this.Controls.Add(this.cbDevicesIP);
            this.Controls.Add(this.btnConnectDevice);
            this.Name = "Form1";
            this.Text = "LP LED Cube 8x8x8";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownRow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownColumn)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnScanDevices;
        private System.Windows.Forms.ComboBox cbDevicesIP;
        private System.Windows.Forms.Button btnConnectDevice;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox editLog;
        private System.Windows.Forms.Timer timerUDPBroadcast;
        private System.Windows.Forms.Button buttonRowSet;
        private System.Windows.Forms.NumericUpDown numericUpDownRow;
        private System.Windows.Forms.CheckBox checkBoxRowState;
        private System.Windows.Forms.Button buttonRowsSet;
        private System.Windows.Forms.CheckBox checkBoxRow1;
        private System.Windows.Forms.CheckBox checkBoxRow2;
        private System.Windows.Forms.CheckBox checkBoxRow3;
        private System.Windows.Forms.CheckBox checkBoxRow6;
        private System.Windows.Forms.CheckBox checkBoxRow5;
        private System.Windows.Forms.CheckBox checkBoxRow4;
        private System.Windows.Forms.CheckBox checkBoxRow8;
        private System.Windows.Forms.CheckBox checkBoxRow7;
        private System.Windows.Forms.Button buttonRowsRead;
        private System.Windows.Forms.CheckBox checkBoxColumnState;
        private System.Windows.Forms.NumericUpDown numericUpDownColumn;
        private System.Windows.Forms.Button buttonColumnSet;
        private LEDGridControl ledGridControl;
        private System.Windows.Forms.Button buttonColumnsSet;
        private System.Windows.Forms.ComboBox cbAnimationsList;
        private System.Windows.Forms.Button btnRefreshAnimationsList;
    }
}

