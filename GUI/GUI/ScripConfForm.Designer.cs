namespace BKWGen3
{
    partial class ScripConfForm
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.numRepeat = new System.Windows.Forms.NumericUpDown();
            this.numDlbefore = new System.Windows.Forms.NumericUpDown();
            this.numDlrepeat = new System.Windows.Forms.NumericUpDown();
            this.numDlafter = new System.Windows.Forms.NumericUpDown();
            this.butOk = new System.Windows.Forms.Button();
            this.butCancel = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.cbbAlign = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numRepeat)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numDlbefore)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numDlrepeat)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numDlafter)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(107, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Delay Before (x20ms)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 21);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(69, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Repeat times";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 75);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(106, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Delay repeat (x20ms)";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 101);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(97, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Delay after (x20ms)";
            // 
            // numRepeat
            // 
            this.numRepeat.Location = new System.Drawing.Point(123, 19);
            this.numRepeat.Maximum = new decimal(new int[] {
            250,
            0,
            0,
            0});
            this.numRepeat.Name = "numRepeat";
            this.numRepeat.Size = new System.Drawing.Size(71, 20);
            this.numRepeat.TabIndex = 1;
            // 
            // numDlbefore
            // 
            this.numDlbefore.Location = new System.Drawing.Point(123, 45);
            this.numDlbefore.Maximum = new decimal(new int[] {
            4500,
            0,
            0,
            0});
            this.numDlbefore.Name = "numDlbefore";
            this.numDlbefore.Size = new System.Drawing.Size(71, 20);
            this.numDlbefore.TabIndex = 2;
            // 
            // numDlrepeat
            // 
            this.numDlrepeat.Location = new System.Drawing.Point(124, 73);
            this.numDlrepeat.Maximum = new decimal(new int[] {
            4500,
            0,
            0,
            0});
            this.numDlrepeat.Name = "numDlrepeat";
            this.numDlrepeat.Size = new System.Drawing.Size(71, 20);
            this.numDlrepeat.TabIndex = 3;
            // 
            // numDlafter
            // 
            this.numDlafter.Location = new System.Drawing.Point(124, 99);
            this.numDlafter.Maximum = new decimal(new int[] {
            4500,
            0,
            0,
            0});
            this.numDlafter.Name = "numDlafter";
            this.numDlafter.Size = new System.Drawing.Size(71, 20);
            this.numDlafter.TabIndex = 4;
            // 
            // butOk
            // 
            this.butOk.Location = new System.Drawing.Point(81, 148);
            this.butOk.Name = "butOk";
            this.butOk.Size = new System.Drawing.Size(50, 23);
            this.butOk.TabIndex = 5;
            this.butOk.Text = "OK";
            this.butOk.UseVisualStyleBackColor = true;
            this.butOk.Click += new System.EventHandler(this.butOk_Click);
            // 
            // butCancel
            // 
            this.butCancel.Location = new System.Drawing.Point(147, 148);
            this.butCancel.Name = "butCancel";
            this.butCancel.Size = new System.Drawing.Size(50, 23);
            this.butCancel.TabIndex = 6;
            this.butCancel.Text = "Cancel";
            this.butCancel.UseVisualStyleBackColor = true;
            this.butCancel.Click += new System.EventHandler(this.butCancel_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.cbbAlign);
            this.groupBox1.Controls.Add(this.numRepeat);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.numDlafter);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.numDlrepeat);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.numDlbefore);
            this.groupBox1.Location = new System.Drawing.Point(3, -3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 145);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            // 
            // cbbAlign
            // 
            this.cbbAlign.FormattingEnabled = true;
            this.cbbAlign.Items.AddRange(new object[] {
            "Left",
            "Right",
            "Center"});
            this.cbbAlign.Location = new System.Drawing.Point(123, 126);
            this.cbbAlign.Name = "cbbAlign";
            this.cbbAlign.Size = new System.Drawing.Size(72, 21);
            this.cbbAlign.TabIndex = 5;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(9, 126);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 13);
            this.label5.TabIndex = 6;
            this.label5.Text = "Alignment";
            // 
            // ScripConfForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(203, 175);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.butCancel);
            this.Controls.Add(this.butOk);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Name = "ScripConfForm";
            this.Text = "Setting";
            ((System.ComponentModel.ISupportInitialize)(this.numRepeat)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numDlbefore)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numDlrepeat)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numDlafter)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown numRepeat;
        private System.Windows.Forms.NumericUpDown numDlbefore;
        private System.Windows.Forms.NumericUpDown numDlrepeat;
        private System.Windows.Forms.NumericUpDown numDlafter;
        private System.Windows.Forms.Button butOk;
        private System.Windows.Forms.Button butCancel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cbbAlign;
    }
}