#pragma once

namespace CTWhack {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для mainform
	/// </summary>
	public ref class mainform : public System::Windows::Forms::Form
	{
	public:
		mainform(void);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~mainform()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^  FreezeTimeEnabled;
	private: System::Windows::Forms::Button^  Set1sBtn;
	private: System::Windows::Forms::Button^  Set30mBtn;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  InfManaEnabled;
	private: System::Windows::Forms::Button^  AttachToGameBtn;
	private: System::Windows::Forms::Timer^  timer1;
	
	private:
		uint8_t * defAsm;
		uint32_t AsmOffset = 0x237439;
		uint32_t CounterOffset = 0x5885F0;	//+0x24
		uint32_t CTWStartAddr = 0;
		uint32_t CounterAddr = 0;
		HANDLE hCTW = NULL;
		HWND hCTWwnd = NULL;
		bool bConn = false;
		float timer = 0;

		bool Connect();
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Требуемый метод для поддержки конструктора — не изменяйте 
			 /// содержимое этого метода с помощью редактора кода.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 this->FreezeTimeEnabled = (gcnew System::Windows::Forms::CheckBox());
				 this->Set1sBtn = (gcnew System::Windows::Forms::Button());
				 this->Set30mBtn = (gcnew System::Windows::Forms::Button());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->InfManaEnabled = (gcnew System::Windows::Forms::CheckBox());
				 this->AttachToGameBtn = (gcnew System::Windows::Forms::Button());
				 this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
				 this->groupBox1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // FreezeTimeEnabled
				 // 
				 this->FreezeTimeEnabled->AutoSize = true;
				 this->FreezeTimeEnabled->Location = System::Drawing::Point(6, 19);
				 this->FreezeTimeEnabled->Name = L"FreezeTimeEnabled";
				 this->FreezeTimeEnabled->Size = System::Drawing::Size(88, 17);
				 this->FreezeTimeEnabled->TabIndex = 0;
				 this->FreezeTimeEnabled->Text = L"Заморозить";
				 this->FreezeTimeEnabled->UseVisualStyleBackColor = true;
				 this->FreezeTimeEnabled->CheckedChanged += gcnew System::EventHandler(this, &mainform::FreezeTimeEnabled_CheckedChanged);
				 // 
				 // Set1sBtn
				 // 
				 this->Set1sBtn->Location = System::Drawing::Point(6, 42);
				 this->Set1sBtn->Name = L"Set1sBtn";
				 this->Set1sBtn->Size = System::Drawing::Size(75, 23);
				 this->Set1sBtn->TabIndex = 1;
				 this->Set1sBtn->Text = L"1 секунда";
				 this->Set1sBtn->UseVisualStyleBackColor = true;
				 this->Set1sBtn->Click += gcnew System::EventHandler(this, &mainform::Set1sBtn_Click);
				 // 
				 // Set30mBtn
				 // 
				 this->Set30mBtn->Location = System::Drawing::Point(87, 42);
				 this->Set30mBtn->Name = L"Set30mBtn";
				 this->Set30mBtn->Size = System::Drawing::Size(75, 23);
				 this->Set30mBtn->TabIndex = 2;
				 this->Set30mBtn->Text = L"30 минут";
				 this->Set30mBtn->UseVisualStyleBackColor = true;
				 this->Set30mBtn->Click += gcnew System::EventHandler(this, &mainform::Set30mBtn_Click);
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->FreezeTimeEnabled);
				 this->groupBox1->Controls->Add(this->Set1sBtn);
				 this->groupBox1->Controls->Add(this->Set30mBtn);
				 this->groupBox1->Location = System::Drawing::Point(2, 54);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(167, 71);
				 this->groupBox1->TabIndex = 3;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"Время до волны монстров";
				 // 
				 // InfManaEnabled
				 // 
				 this->InfManaEnabled->AutoSize = true;
				 this->InfManaEnabled->Location = System::Drawing::Point(8, 31);
				 this->InfManaEnabled->Name = L"InfManaEnabled";
				 this->InfManaEnabled->Size = System::Drawing::Size(121, 17);
				 this->InfManaEnabled->TabIndex = 4;
				 this->InfManaEnabled->Text = L"Бесконечная мана";
				 this->InfManaEnabled->UseVisualStyleBackColor = true;
				 this->InfManaEnabled->CheckedChanged += gcnew System::EventHandler(this, &mainform::InfManaEnabled_CheckedChanged);
				 // 
				 // AttachToGameBtn
				 // 
				 this->AttachToGameBtn->Location = System::Drawing::Point(2, 2);
				 this->AttachToGameBtn->Name = L"AttachToGameBtn";
				 this->AttachToGameBtn->Size = System::Drawing::Size(167, 23);
				 this->AttachToGameBtn->TabIndex = 5;
				 this->AttachToGameBtn->Text = L"Подключиться к игре";
				 this->AttachToGameBtn->UseVisualStyleBackColor = true;
				 this->AttachToGameBtn->Click += gcnew System::EventHandler(this, &mainform::AttachToGameBtn_Click);
				 // 
				 // timer1
				 // 
				 this->timer1->Tick += gcnew System::EventHandler(this, &mainform::UpdateCounter);
				 // 
				 // mainform
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(172, 128);
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				 this->Controls->Add(this->AttachToGameBtn);
				 this->Controls->Add(this->InfManaEnabled);
				 this->Controls->Add(this->groupBox1);
				 this->Name = L"mainform";
				 this->Text = L"CTWhack";
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void InfManaEnabled_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void AttachToGameBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void FreezeTimeEnabled_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void UpdateCounter(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Set1sBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Set30mBtn_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
