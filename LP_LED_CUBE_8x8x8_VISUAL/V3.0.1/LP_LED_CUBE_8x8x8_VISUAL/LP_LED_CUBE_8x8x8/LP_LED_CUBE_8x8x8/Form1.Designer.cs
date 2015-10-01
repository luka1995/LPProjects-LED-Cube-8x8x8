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
            this.cbAnimationsList = new System.Windows.Forms.ComboBox();
            this.btnRefreshAnimationsList = new System.Windows.Forms.Button();
            this.buttonPlayAnimation = new System.Windows.Forms.Button();
            this.buttonStopAnimation = new System.Windows.Forms.Button();
            this.buttonSaveAnimationFile = new System.Windows.Forms.Button();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.dataGridViewAnimation = new System.Windows.Forms.DataGridView();
            this.NumberColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.nameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.lEDCUBEEffectBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.checkBoxRow8 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow7 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow6 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow5 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow4 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow3 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow2 = new System.Windows.Forms.CheckBox();
            this.checkBoxRow1 = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxEffectName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.numericUpDownEffectDelay = new System.Windows.Forms.NumericUpDown();
            this.buttonNewEffect = new System.Windows.Forms.Button();
            this.buttonDeleteEffect = new System.Windows.Forms.Button();
            this.buttonDeleteAllEffect = new System.Windows.Forms.Button();
            this.buttonLoadAnimationFile = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.buttonCopyEffect = new System.Windows.Forms.Button();
            this.buttonDeleteAnimation = new System.Windows.Forms.Button();
            this.buttonUpload = new System.Windows.Forms.Button();
            this.textBoxNewAnimationName = new System.Windows.Forms.TextBox();
            this.ledGridControl = new LP_LED_CUBE_8x8x8.LEDGridControl();
            this.buttonSelectAllColumns = new System.Windows.Forms.Button();
            this.buttonDeselectAllColumns = new System.Windows.Forms.Button();
            this.buttonAppendFile = new System.Windows.Forms.Button();
            this.buttonAllRowsON = new System.Windows.Forms.Button();
            this.buttonAllRowsOFF = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAnimation)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lEDCUBEEffectBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEffectDelay)).BeginInit();
            this.SuspendLayout();
            // 
            // btnScanDevices
            // 
            this.btnScanDevices.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnScanDevices.Location = new System.Drawing.Point(8, 8);
            this.btnScanDevices.Name = "btnScanDevices";
            this.btnScanDevices.Size = new System.Drawing.Size(75, 22);
            this.btnScanDevices.TabIndex = 38;
            this.btnScanDevices.Text = "Scan";
            this.btnScanDevices.Click += new System.EventHandler(this.btnScanDevices_Click);
            // 
            // cbDevicesIP
            // 
            this.cbDevicesIP.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.cbDevicesIP.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDevicesIP.Enabled = false;
            this.cbDevicesIP.FormattingEnabled = true;
            this.cbDevicesIP.Location = new System.Drawing.Point(90, 8);
            this.cbDevicesIP.MaxDropDownItems = 100;
            this.cbDevicesIP.Name = "cbDevicesIP";
            this.cbDevicesIP.Size = new System.Drawing.Size(119, 21);
            this.cbDevicesIP.TabIndex = 36;
            // 
            // btnConnectDevice
            // 
            this.btnConnectDevice.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnConnectDevice.Enabled = false;
            this.btnConnectDevice.Location = new System.Drawing.Point(216, 7);
            this.btnConnectDevice.Name = "btnConnectDevice";
            this.btnConnectDevice.Size = new System.Drawing.Size(88, 22);
            this.btnConnectDevice.TabIndex = 37;
            this.btnConnectDevice.Text = "Connect";
            this.btnConnectDevice.Click += new System.EventHandler(this.btnConnectDevice_Click);
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(8, 456);
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
            this.editLog.Location = new System.Drawing.Point(11, 477);
            this.editLog.Multiline = true;
            this.editLog.Name = "editLog";
            this.editLog.ReadOnly = true;
            this.editLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.editLog.Size = new System.Drawing.Size(733, 56);
            this.editLog.TabIndex = 39;
            // 
            // timerUDPBroadcast
            // 
            this.timerUDPBroadcast.Tick += new System.EventHandler(this.timerUDPBroadcast_Tick);
            // 
            // cbAnimationsList
            // 
            this.cbAnimationsList.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.cbAnimationsList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbAnimationsList.Enabled = false;
            this.cbAnimationsList.FormattingEnabled = true;
            this.cbAnimationsList.Location = new System.Drawing.Point(432, 7);
            this.cbAnimationsList.Name = "cbAnimationsList";
            this.cbAnimationsList.Size = new System.Drawing.Size(152, 21);
            this.cbAnimationsList.TabIndex = 61;
            // 
            // btnRefreshAnimationsList
            // 
            this.btnRefreshAnimationsList.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnRefreshAnimationsList.Enabled = false;
            this.btnRefreshAnimationsList.Location = new System.Drawing.Point(350, 6);
            this.btnRefreshAnimationsList.Name = "btnRefreshAnimationsList";
            this.btnRefreshAnimationsList.Size = new System.Drawing.Size(75, 23);
            this.btnRefreshAnimationsList.TabIndex = 60;
            this.btnRefreshAnimationsList.Text = "Refresh List";
            this.btnRefreshAnimationsList.UseVisualStyleBackColor = true;
            this.btnRefreshAnimationsList.Click += new System.EventHandler(this.btnRefreshAnimationsList_Click);
            // 
            // buttonPlayAnimation
            // 
            this.buttonPlayAnimation.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonPlayAnimation.Enabled = false;
            this.buttonPlayAnimation.Location = new System.Drawing.Point(657, 6);
            this.buttonPlayAnimation.Name = "buttonPlayAnimation";
            this.buttonPlayAnimation.Size = new System.Drawing.Size(43, 23);
            this.buttonPlayAnimation.TabIndex = 62;
            this.buttonPlayAnimation.Text = "Start";
            this.buttonPlayAnimation.UseVisualStyleBackColor = true;
            this.buttonPlayAnimation.Click += new System.EventHandler(this.buttonPlayAnimation_Click);
            // 
            // buttonStopAnimation
            // 
            this.buttonStopAnimation.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonStopAnimation.Enabled = false;
            this.buttonStopAnimation.Location = new System.Drawing.Point(705, 6);
            this.buttonStopAnimation.Name = "buttonStopAnimation";
            this.buttonStopAnimation.Size = new System.Drawing.Size(39, 23);
            this.buttonStopAnimation.TabIndex = 64;
            this.buttonStopAnimation.Text = "Stop";
            this.buttonStopAnimation.UseVisualStyleBackColor = true;
            this.buttonStopAnimation.Click += new System.EventHandler(this.buttonStopAnimation_Click);
            // 
            // buttonSaveAnimationFile
            // 
            this.buttonSaveAnimationFile.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonSaveAnimationFile.Location = new System.Drawing.Point(10, 431);
            this.buttonSaveAnimationFile.Name = "buttonSaveAnimationFile";
            this.buttonSaveAnimationFile.Size = new System.Drawing.Size(114, 23);
            this.buttonSaveAnimationFile.TabIndex = 65;
            this.buttonSaveAnimationFile.Text = "Save Animation File";
            this.buttonSaveAnimationFile.UseVisualStyleBackColor = true;
            this.buttonSaveAnimationFile.Click += new System.EventHandler(this.buttonFileSave_Click);
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialog_FileOk);
            // 
            // dataGridViewAnimation
            // 
            this.dataGridViewAnimation.AllowUserToAddRows = false;
            this.dataGridViewAnimation.AllowUserToResizeColumns = false;
            this.dataGridViewAnimation.AllowUserToResizeRows = false;
            this.dataGridViewAnimation.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.dataGridViewAnimation.AutoGenerateColumns = false;
            this.dataGridViewAnimation.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewAnimation.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.NumberColumn,
            this.nameDataGridViewTextBoxColumn});
            this.dataGridViewAnimation.DataSource = this.lEDCUBEEffectBindingSource;
            this.dataGridViewAnimation.Location = new System.Drawing.Point(9, 38);
            this.dataGridViewAnimation.MultiSelect = false;
            this.dataGridViewAnimation.Name = "dataGridViewAnimation";
            this.dataGridViewAnimation.RowHeadersVisible = false;
            this.dataGridViewAnimation.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewAnimation.Size = new System.Drawing.Size(220, 360);
            this.dataGridViewAnimation.TabIndex = 66;
            this.dataGridViewAnimation.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.dataGridViewAnimation_CellFormatting);
            // 
            // NumberColumn
            // 
            this.NumberColumn.FillWeight = 40F;
            this.NumberColumn.HeaderText = "Number";
            this.NumberColumn.Name = "NumberColumn";
            this.NumberColumn.ReadOnly = true;
            this.NumberColumn.Width = 50;
            // 
            // nameDataGridViewTextBoxColumn
            // 
            this.nameDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.nameDataGridViewTextBoxColumn.DataPropertyName = "name";
            this.nameDataGridViewTextBoxColumn.HeaderText = "Name";
            this.nameDataGridViewTextBoxColumn.Name = "nameDataGridViewTextBoxColumn";
            // 
            // lEDCUBEEffectBindingSource
            // 
            this.lEDCUBEEffectBindingSource.DataSource = typeof(LED_CUBE_Effect);
            // 
            // checkBoxRow8
            // 
            this.checkBoxRow8.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.checkBoxRow8.AutoSize = true;
            this.checkBoxRow8.DataBindings.Add(new System.Windows.Forms.Binding("Checked", this.lEDCUBEEffectBindingSource, "chk8", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.checkBoxRow8.Location = new System.Drawing.Point(652, 217);
            this.checkBoxRow8.Name = "checkBoxRow8";
            this.checkBoxRow8.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow8.TabIndex = 75;
            this.checkBoxRow8.Text = "Row 8";
            this.checkBoxRow8.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow7
            // 
            this.checkBoxRow7.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.checkBoxRow7.AutoSize = true;
            this.checkBoxRow7.DataBindings.Add(new System.Windows.Forms.Binding("Checked", this.lEDCUBEEffectBindingSource, "chk7", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.checkBoxRow7.Location = new System.Drawing.Point(652, 194);
            this.checkBoxRow7.Name = "checkBoxRow7";
            this.checkBoxRow7.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow7.TabIndex = 74;
            this.checkBoxRow7.Text = "Row 7";
            this.checkBoxRow7.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow6
            // 
            this.checkBoxRow6.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.checkBoxRow6.AutoSize = true;
            this.checkBoxRow6.DataBindings.Add(new System.Windows.Forms.Binding("Checked", this.lEDCUBEEffectBindingSource, "chk6", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.checkBoxRow6.Location = new System.Drawing.Point(652, 171);
            this.checkBoxRow6.Name = "checkBoxRow6";
            this.checkBoxRow6.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow6.TabIndex = 73;
            this.checkBoxRow6.Text = "Row 6";
            this.checkBoxRow6.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow5
            // 
            this.checkBoxRow5.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.checkBoxRow5.AutoSize = true;
            this.checkBoxRow5.DataBindings.Add(new System.Windows.Forms.Binding("Checked", this.lEDCUBEEffectBindingSource, "chk5", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.checkBoxRow5.Location = new System.Drawing.Point(652, 148);
            this.checkBoxRow5.Name = "checkBoxRow5";
            this.checkBoxRow5.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow5.TabIndex = 72;
            this.checkBoxRow5.Text = "Row 5";
            this.checkBoxRow5.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow4
            // 
            this.checkBoxRow4.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.checkBoxRow4.AutoSize = true;
            this.checkBoxRow4.DataBindings.Add(new System.Windows.Forms.Binding("Checked", this.lEDCUBEEffectBindingSource, "chk4", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.checkBoxRow4.Location = new System.Drawing.Point(652, 125);
            this.checkBoxRow4.Name = "checkBoxRow4";
            this.checkBoxRow4.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow4.TabIndex = 71;
            this.checkBoxRow4.Text = "Row 4";
            this.checkBoxRow4.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow3
            // 
            this.checkBoxRow3.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.checkBoxRow3.AutoSize = true;
            this.checkBoxRow3.DataBindings.Add(new System.Windows.Forms.Binding("Checked", this.lEDCUBEEffectBindingSource, "chk3", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.checkBoxRow3.Location = new System.Drawing.Point(652, 104);
            this.checkBoxRow3.Name = "checkBoxRow3";
            this.checkBoxRow3.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow3.TabIndex = 70;
            this.checkBoxRow3.Text = "Row 3";
            this.checkBoxRow3.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow2
            // 
            this.checkBoxRow2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.checkBoxRow2.AutoSize = true;
            this.checkBoxRow2.DataBindings.Add(new System.Windows.Forms.Binding("Checked", this.lEDCUBEEffectBindingSource, "chk2", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.checkBoxRow2.Location = new System.Drawing.Point(652, 81);
            this.checkBoxRow2.Name = "checkBoxRow2";
            this.checkBoxRow2.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow2.TabIndex = 69;
            this.checkBoxRow2.Text = "Row 2";
            this.checkBoxRow2.UseVisualStyleBackColor = true;
            // 
            // checkBoxRow1
            // 
            this.checkBoxRow1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.checkBoxRow1.AutoSize = true;
            this.checkBoxRow1.DataBindings.Add(new System.Windows.Forms.Binding("Checked", this.lEDCUBEEffectBindingSource, "chk1", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.checkBoxRow1.Location = new System.Drawing.Point(652, 58);
            this.checkBoxRow1.Name = "checkBoxRow1";
            this.checkBoxRow1.Size = new System.Drawing.Size(57, 17);
            this.checkBoxRow1.TabIndex = 68;
            this.checkBoxRow1.Text = "Row 1";
            this.checkBoxRow1.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(238, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(67, 16);
            this.label1.TabIndex = 76;
            this.label1.Text = "Columns";
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(649, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(46, 16);
            this.label2.TabIndex = 77;
            this.label2.Text = "Rows";
            // 
            // textBoxEffectName
            // 
            this.textBoxEffectName.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.textBoxEffectName.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.lEDCUBEEffectBindingSource, "name", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.textBoxEffectName.Location = new System.Drawing.Point(624, 369);
            this.textBoxEffectName.MaxLength = 20;
            this.textBoxEffectName.Name = "textBoxEffectName";
            this.textBoxEffectName.Size = new System.Drawing.Size(120, 20);
            this.textBoxEffectName.TabIndex = 78;
            this.textBoxEffectName.Text = "Effect";
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(621, 350);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(49, 16);
            this.label3.TabIndex = 79;
            this.label3.Text = "Name";
            // 
            // label5
            // 
            this.label5.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(621, 305);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(49, 16);
            this.label5.TabIndex = 81;
            this.label5.Text = "Delay";
            // 
            // numericUpDownEffectDelay
            // 
            this.numericUpDownEffectDelay.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numericUpDownEffectDelay.DataBindings.Add(new System.Windows.Forms.Binding("Value", this.lEDCUBEEffectBindingSource, "delay", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.numericUpDownEffectDelay.Location = new System.Drawing.Point(624, 324);
            this.numericUpDownEffectDelay.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDownEffectDelay.Name = "numericUpDownEffectDelay";
            this.numericUpDownEffectDelay.Size = new System.Drawing.Size(120, 20);
            this.numericUpDownEffectDelay.TabIndex = 83;
            // 
            // buttonNewEffect
            // 
            this.buttonNewEffect.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonNewEffect.Location = new System.Drawing.Point(10, 404);
            this.buttonNewEffect.Name = "buttonNewEffect";
            this.buttonNewEffect.Size = new System.Drawing.Size(41, 23);
            this.buttonNewEffect.TabIndex = 84;
            this.buttonNewEffect.Text = "New";
            this.buttonNewEffect.UseVisualStyleBackColor = true;
            this.buttonNewEffect.Click += new System.EventHandler(this.buttonNewEffect_Click);
            // 
            // buttonDeleteEffect
            // 
            this.buttonDeleteEffect.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonDeleteEffect.Location = new System.Drawing.Point(57, 404);
            this.buttonDeleteEffect.Name = "buttonDeleteEffect";
            this.buttonDeleteEffect.Size = new System.Drawing.Size(46, 23);
            this.buttonDeleteEffect.TabIndex = 85;
            this.buttonDeleteEffect.Text = "Delete";
            this.buttonDeleteEffect.UseVisualStyleBackColor = true;
            this.buttonDeleteEffect.Click += new System.EventHandler(this.buttonDeleteEffect_Click);
            // 
            // buttonDeleteAllEffect
            // 
            this.buttonDeleteAllEffect.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonDeleteAllEffect.Location = new System.Drawing.Point(109, 404);
            this.buttonDeleteAllEffect.Name = "buttonDeleteAllEffect";
            this.buttonDeleteAllEffect.Size = new System.Drawing.Size(60, 23);
            this.buttonDeleteAllEffect.TabIndex = 86;
            this.buttonDeleteAllEffect.Text = "Delete All";
            this.buttonDeleteAllEffect.UseVisualStyleBackColor = true;
            this.buttonDeleteAllEffect.Click += new System.EventHandler(this.buttonDeleteAllEffect_Click);
            // 
            // buttonLoadAnimationFile
            // 
            this.buttonLoadAnimationFile.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonLoadAnimationFile.Location = new System.Drawing.Point(130, 431);
            this.buttonLoadAnimationFile.Name = "buttonLoadAnimationFile";
            this.buttonLoadAnimationFile.Size = new System.Drawing.Size(100, 23);
            this.buttonLoadAnimationFile.TabIndex = 87;
            this.buttonLoadAnimationFile.Text = "Load Animation File";
            this.buttonLoadAnimationFile.UseVisualStyleBackColor = true;
            this.buttonLoadAnimationFile.Click += new System.EventHandler(this.buttonLoadAnimationFile_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog";
            this.openFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog_FileOk);
            // 
            // buttonCopyEffect
            // 
            this.buttonCopyEffect.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonCopyEffect.Location = new System.Drawing.Point(175, 404);
            this.buttonCopyEffect.Name = "buttonCopyEffect";
            this.buttonCopyEffect.Size = new System.Drawing.Size(55, 23);
            this.buttonCopyEffect.TabIndex = 88;
            this.buttonCopyEffect.Text = "Copy";
            this.buttonCopyEffect.UseVisualStyleBackColor = true;
            this.buttonCopyEffect.Click += new System.EventHandler(this.buttonCopyEffect_Click);
            // 
            // buttonDeleteAnimation
            // 
            this.buttonDeleteAnimation.Enabled = false;
            this.buttonDeleteAnimation.Location = new System.Drawing.Point(591, 6);
            this.buttonDeleteAnimation.Name = "buttonDeleteAnimation";
            this.buttonDeleteAnimation.Size = new System.Drawing.Size(60, 23);
            this.buttonDeleteAnimation.TabIndex = 89;
            this.buttonDeleteAnimation.Text = "Delete";
            this.buttonDeleteAnimation.UseVisualStyleBackColor = true;
            this.buttonDeleteAnimation.Click += new System.EventHandler(this.buttonDeleteAnimation_Click);
            // 
            // buttonUpload
            // 
            this.buttonUpload.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonUpload.Enabled = false;
            this.buttonUpload.Location = new System.Drawing.Point(665, 431);
            this.buttonUpload.Name = "buttonUpload";
            this.buttonUpload.Size = new System.Drawing.Size(80, 23);
            this.buttonUpload.TabIndex = 90;
            this.buttonUpload.Text = "Upload";
            this.buttonUpload.UseVisualStyleBackColor = true;
            this.buttonUpload.Click += new System.EventHandler(this.buttonUpload_Click);
            // 
            // textBoxNewAnimationName
            // 
            this.textBoxNewAnimationName.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxNewAnimationName.Enabled = false;
            this.textBoxNewAnimationName.Location = new System.Drawing.Point(499, 433);
            this.textBoxNewAnimationName.Name = "textBoxNewAnimationName";
            this.textBoxNewAnimationName.Size = new System.Drawing.Size(160, 20);
            this.textBoxNewAnimationName.TabIndex = 91;
            // 
            // ledGridControl
            // 
            this.ledGridControl.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.ledGridControl.CheckedBytes = new byte[] {
        ((byte)(0)),
        ((byte)(0)),
        ((byte)(0)),
        ((byte)(0)),
        ((byte)(0)),
        ((byte)(0)),
        ((byte)(0)),
        ((byte)(0))};
            this.ledGridControl.DataBindings.Add(new System.Windows.Forms.Binding("CheckedBytes", this.lEDCUBEEffectBindingSource, "columns", true));
            this.ledGridControl.Location = new System.Drawing.Point(245, 59);
            this.ledGridControl.Name = "ledGridControl";
            this.ledGridControl.Size = new System.Drawing.Size(350, 339);
            this.ledGridControl.TabIndex = 67;
            this.ledGridControl.Text = "ledGridControl";
            // 
            // buttonSelectAllColumns
            // 
            this.buttonSelectAllColumns.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonSelectAllColumns.Location = new System.Drawing.Point(241, 404);
            this.buttonSelectAllColumns.Name = "buttonSelectAllColumns";
            this.buttonSelectAllColumns.Size = new System.Drawing.Size(108, 23);
            this.buttonSelectAllColumns.TabIndex = 92;
            this.buttonSelectAllColumns.Text = "All Columns ON";
            this.buttonSelectAllColumns.UseVisualStyleBackColor = true;
            this.buttonSelectAllColumns.Click += new System.EventHandler(this.buttonSelectAllColumns_Click);
            // 
            // buttonDeselectAllColumns
            // 
            this.buttonDeselectAllColumns.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonDeselectAllColumns.Location = new System.Drawing.Point(355, 404);
            this.buttonDeselectAllColumns.Name = "buttonDeselectAllColumns";
            this.buttonDeselectAllColumns.Size = new System.Drawing.Size(108, 23);
            this.buttonDeselectAllColumns.TabIndex = 93;
            this.buttonDeselectAllColumns.Text = "All Columns OFF";
            this.buttonDeselectAllColumns.UseVisualStyleBackColor = true;
            this.buttonDeselectAllColumns.Click += new System.EventHandler(this.buttonDeselectAllColumns_Click);
            // 
            // buttonAppendFile
            // 
            this.buttonAppendFile.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonAppendFile.Location = new System.Drawing.Point(241, 431);
            this.buttonAppendFile.Name = "buttonAppendFile";
            this.buttonAppendFile.Size = new System.Drawing.Size(108, 23);
            this.buttonAppendFile.TabIndex = 94;
            this.buttonAppendFile.Text = "Append File";
            this.buttonAppendFile.UseVisualStyleBackColor = true;
            this.buttonAppendFile.Click += new System.EventHandler(this.buttonAppendFile_Click);
            // 
            // buttonAllRowsON
            // 
            this.buttonAllRowsON.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonAllRowsON.Location = new System.Drawing.Point(523, 404);
            this.buttonAllRowsON.Name = "buttonAllRowsON";
            this.buttonAllRowsON.Size = new System.Drawing.Size(108, 23);
            this.buttonAllRowsON.TabIndex = 95;
            this.buttonAllRowsON.Text = "All Rows ON";
            this.buttonAllRowsON.UseVisualStyleBackColor = true;
            this.buttonAllRowsON.Click += new System.EventHandler(this.buttonAllRowsON_Click);
            // 
            // buttonAllRowsOFF
            // 
            this.buttonAllRowsOFF.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonAllRowsOFF.Location = new System.Drawing.Point(637, 404);
            this.buttonAllRowsOFF.Name = "buttonAllRowsOFF";
            this.buttonAllRowsOFF.Size = new System.Drawing.Size(108, 23);
            this.buttonAllRowsOFF.TabIndex = 96;
            this.buttonAllRowsOFF.Text = "All Rows OFF";
            this.buttonAllRowsOFF.UseVisualStyleBackColor = true;
            this.buttonAllRowsOFF.Click += new System.EventHandler(this.buttonAllRowsOFF_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(754, 542);
            this.Controls.Add(this.buttonAllRowsOFF);
            this.Controls.Add(this.buttonAllRowsON);
            this.Controls.Add(this.buttonAppendFile);
            this.Controls.Add(this.buttonDeselectAllColumns);
            this.Controls.Add(this.buttonSelectAllColumns);
            this.Controls.Add(this.textBoxNewAnimationName);
            this.Controls.Add(this.buttonUpload);
            this.Controls.Add(this.buttonDeleteAnimation);
            this.Controls.Add(this.buttonCopyEffect);
            this.Controls.Add(this.buttonLoadAnimationFile);
            this.Controls.Add(this.buttonDeleteAllEffect);
            this.Controls.Add(this.buttonDeleteEffect);
            this.Controls.Add(this.buttonNewEffect);
            this.Controls.Add(this.numericUpDownEffectDelay);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBoxEffectName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.checkBoxRow8);
            this.Controls.Add(this.checkBoxRow7);
            this.Controls.Add(this.checkBoxRow6);
            this.Controls.Add(this.checkBoxRow5);
            this.Controls.Add(this.checkBoxRow4);
            this.Controls.Add(this.checkBoxRow3);
            this.Controls.Add(this.checkBoxRow2);
            this.Controls.Add(this.checkBoxRow1);
            this.Controls.Add(this.ledGridControl);
            this.Controls.Add(this.dataGridViewAnimation);
            this.Controls.Add(this.buttonSaveAnimationFile);
            this.Controls.Add(this.buttonStopAnimation);
            this.Controls.Add(this.buttonPlayAnimation);
            this.Controls.Add(this.cbAnimationsList);
            this.Controls.Add(this.btnRefreshAnimationsList);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.editLog);
            this.Controls.Add(this.btnScanDevices);
            this.Controls.Add(this.cbDevicesIP);
            this.Controls.Add(this.btnConnectDevice);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(770, 580);
            this.MinimumSize = new System.Drawing.Size(770, 580);
            this.Name = "Form1";
            this.ShowIcon = false;
            this.Text = "LP LED Cube 8x8x8";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAnimation)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lEDCUBEEffectBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEffectDelay)).EndInit();
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
        private System.Windows.Forms.ComboBox cbAnimationsList;
        private System.Windows.Forms.Button btnRefreshAnimationsList;
        private System.Windows.Forms.Button buttonPlayAnimation;
        private System.Windows.Forms.Button buttonStopAnimation;
        private System.Windows.Forms.Button buttonSaveAnimationFile;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.DataGridView dataGridViewAnimation;
        private System.Windows.Forms.BindingSource lEDCUBEEffectBindingSource;
        private LEDGridControl ledGridControl;
        private System.Windows.Forms.CheckBox checkBoxRow8;
        private System.Windows.Forms.CheckBox checkBoxRow7;
        private System.Windows.Forms.CheckBox checkBoxRow6;
        private System.Windows.Forms.CheckBox checkBoxRow5;
        private System.Windows.Forms.CheckBox checkBoxRow4;
        private System.Windows.Forms.CheckBox checkBoxRow3;
        private System.Windows.Forms.CheckBox checkBoxRow2;
        private System.Windows.Forms.CheckBox checkBoxRow1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxEffectName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown numericUpDownEffectDelay;
        private System.Windows.Forms.Button buttonNewEffect;
        private System.Windows.Forms.Button buttonDeleteEffect;
        private System.Windows.Forms.Button buttonDeleteAllEffect;
        private System.Windows.Forms.DataGridViewTextBoxColumn NumberColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn nameDataGridViewTextBoxColumn;
        private System.Windows.Forms.Button buttonLoadAnimationFile;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Button buttonCopyEffect;
        private System.Windows.Forms.Button buttonDeleteAnimation;
        private System.Windows.Forms.Button buttonUpload;
        private System.Windows.Forms.TextBox textBoxNewAnimationName;
        private System.Windows.Forms.Button buttonSelectAllColumns;
        private System.Windows.Forms.Button buttonDeselectAllColumns;
        private System.Windows.Forms.Button buttonAppendFile;
        private System.Windows.Forms.Button buttonAllRowsON;
        private System.Windows.Forms.Button buttonAllRowsOFF;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
    }
}

