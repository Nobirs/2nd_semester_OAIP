#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <regex>
#include <Windows.h>
#include <msclr\marshal_cppstd.h>
#include <tuple>

#include "list.h"

using namespace std::literals::string_literals;


namespace My3labWinForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DLListForm
	/// </summary>
	public ref class DLListForm : public System::Windows::Forms::Form
	{
	public:
		DLListForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			list = new LinkedList();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DLListForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ inputTextBox;
	private: System::Windows::Forms::Button^ createBtn;
	private: System::Windows::Forms::Button^ addBtn;
	private: System::Windows::Forms::Button^ printBtn;
	private: System::Windows::Forms::Button^ clearBtn;
	private: System::Windows::Forms::Button^ exitBtn;

	private: System::Windows::Forms::RadioButton^ endRadioBtn;
	private: System::Windows::Forms::RadioButton^ beginRadioBtn;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::TextBox^ outTextBox;
	private: System::Windows::Forms::Panel^ panel2;

	private:
		bool fromBegin = true;
	private: System::Windows::Forms::Button^ taskBtn;
	private: System::Windows::Forms::Button^ clearViewBtn;
		   LinkedList* list = nullptr;



	protected:
	void printText(String^ text) {
		this->outTextBox->AppendText(text);
		this->outTextBox->AppendText(Environment::NewLine);
	}


	std::tuple<bool, int> IntValidator(String^ inputRaw) {
		static const std::regex re(R"(^-?[0-9]+)"s);
		std::smatch match;
		std::string input = msclr::interop::marshal_as<std::string>(inputRaw);
		if (regex_match(input, match, re))
		{
			int value = stoi(input);
			return { true, value };
		}
		std::cerr << "Incorrect input. Try again..." << std::endl;
		return { false, -1 };
	}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->createBtn = (gcnew System::Windows::Forms::Button());
			this->addBtn = (gcnew System::Windows::Forms::Button());
			this->printBtn = (gcnew System::Windows::Forms::Button());
			this->clearBtn = (gcnew System::Windows::Forms::Button());
			this->exitBtn = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->taskBtn = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->endRadioBtn = (gcnew System::Windows::Forms::RadioButton());
			this->beginRadioBtn = (gcnew System::Windows::Forms::RadioButton());
			this->outTextBox = (gcnew System::Windows::Forms::TextBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->clearViewBtn = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(239, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Введите информацию:";
			this->label1->Click += gcnew System::EventHandler(this, &DLListForm::label1_Click);
			// 
			// inputTextBox
			// 
			this->inputTextBox->Location = System::Drawing::Point(275, 16);
			this->inputTextBox->Name = L"inputTextBox";
			this->inputTextBox->Size = System::Drawing::Size(100, 31);
			this->inputTextBox->TabIndex = 1;
			// 
			// createBtn
			// 
			this->createBtn->Location = System::Drawing::Point(49, 36);
			this->createBtn->Name = L"createBtn";
			this->createBtn->Size = System::Drawing::Size(165, 43);
			this->createBtn->TabIndex = 3;
			this->createBtn->Text = L"Создать";
			this->createBtn->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->createBtn->UseVisualStyleBackColor = true;
			this->createBtn->Click += gcnew System::EventHandler(this, &DLListForm::createBtn_Click);
			// 
			// addBtn
			// 
			this->addBtn->Location = System::Drawing::Point(49, 85);
			this->addBtn->Name = L"addBtn";
			this->addBtn->Size = System::Drawing::Size(165, 37);
			this->addBtn->TabIndex = 4;
			this->addBtn->Text = L"Добавить";
			this->addBtn->UseVisualStyleBackColor = true;
			this->addBtn->Click += gcnew System::EventHandler(this, &DLListForm::addBtn_Click);
			// 
			// printBtn
			// 
			this->printBtn->Location = System::Drawing::Point(49, 128);
			this->printBtn->Name = L"printBtn";
			this->printBtn->Size = System::Drawing::Size(165, 40);
			this->printBtn->TabIndex = 5;
			this->printBtn->Text = L"Просмотреть";
			this->printBtn->UseVisualStyleBackColor = true;
			this->printBtn->Click += gcnew System::EventHandler(this, &DLListForm::printBtn_Click);
			// 
			// clearBtn
			// 
			this->clearBtn->Location = System::Drawing::Point(49, 174);
			this->clearBtn->Name = L"clearBtn";
			this->clearBtn->Size = System::Drawing::Size(165, 44);
			this->clearBtn->TabIndex = 6;
			this->clearBtn->Text = L"Очистить";
			this->clearBtn->UseVisualStyleBackColor = true;
			this->clearBtn->Click += gcnew System::EventHandler(this, &DLListForm::clearBtn_Click);
			// 
			// exitBtn
			// 
			this->exitBtn->Location = System::Drawing::Point(49, 224);
			this->exitBtn->Name = L"exitBtn";
			this->exitBtn->Size = System::Drawing::Size(165, 39);
			this->exitBtn->TabIndex = 7;
			this->exitBtn->Text = L"EXIT";
			this->exitBtn->UseVisualStyleBackColor = true;
			this->exitBtn->Click += gcnew System::EventHandler(this, &DLListForm::exitBtn_Click);
			// 
			// panel1
			// 
			this->panel1->AllowDrop = true;
			this->panel1->AutoSize = true;
			this->panel1->Controls->Add(this->taskBtn);
			this->panel1->Controls->Add(this->exitBtn);
			this->panel1->Controls->Add(this->createBtn);
			this->panel1->Controls->Add(this->clearBtn);
			this->panel1->Controls->Add(this->addBtn);
			this->panel1->Controls->Add(this->printBtn);
			this->panel1->Location = System::Drawing::Point(527, 160);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(217, 323);
			this->panel1->TabIndex = 8;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &DLListForm::panel1_Paint);
			// 
			// taskBtn
			// 
			this->taskBtn->Location = System::Drawing::Point(49, 270);
			this->taskBtn->Name = L"taskBtn";
			this->taskBtn->Size = System::Drawing::Size(165, 44);
			this->taskBtn->TabIndex = 8;
			this->taskBtn->Text = L"Task";
			this->taskBtn->UseVisualStyleBackColor = true;
			this->taskBtn->Click += gcnew System::EventHandler(this, &DLListForm::taskBtn_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->endRadioBtn);
			this->groupBox1->Controls->Add(this->beginRadioBtn);
			this->groupBox1->Location = System::Drawing::Point(527, 518);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(287, 139);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Выбор точки входа";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &DLListForm::groupBox1_Enter);
			// 
			// endRadioBtn
			// 
			this->endRadioBtn->AutoSize = true;
			this->endRadioBtn->Location = System::Drawing::Point(47, 85);
			this->endRadioBtn->Name = L"endRadioBtn";
			this->endRadioBtn->Size = System::Drawing::Size(81, 29);
			this->endRadioBtn->TabIndex = 1;
			this->endRadioBtn->Text = L"End";
			this->endRadioBtn->UseVisualStyleBackColor = true;
			this->endRadioBtn->CheckedChanged += gcnew System::EventHandler(this, &DLListForm::radioBtnChanged);
			// 
			// beginRadioBtn
			// 
			this->beginRadioBtn->AutoSize = true;
			this->beginRadioBtn->Checked = true;
			this->beginRadioBtn->Location = System::Drawing::Point(47, 49);
			this->beginRadioBtn->Name = L"beginRadioBtn";
			this->beginRadioBtn->Size = System::Drawing::Size(98, 29);
			this->beginRadioBtn->TabIndex = 0;
			this->beginRadioBtn->TabStop = true;
			this->beginRadioBtn->Text = L"Begin";
			this->beginRadioBtn->UseVisualStyleBackColor = true;
			// 
			// outTextBox
			// 
			this->outTextBox->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->outTextBox->Location = System::Drawing::Point(3, 3);
			this->outTextBox->Multiline = true;
			this->outTextBox->Name = L"outTextBox";
			this->outTextBox->ReadOnly = true;
			this->outTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->outTextBox->Size = System::Drawing::Size(495, 580);
			this->outTextBox->TabIndex = 10;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->inputTextBox);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Location = System::Drawing::Point(525, 76);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(378, 65);
			this->panel2->TabIndex = 11;
			// 
			// clearViewBtn
			// 
			this->clearViewBtn->Location = System::Drawing::Point(141, 609);
			this->clearViewBtn->Name = L"clearViewBtn";
			this->clearViewBtn->Size = System::Drawing::Size(186, 48);
			this->clearViewBtn->TabIndex = 12;
			this->clearViewBtn->Text = L"Очистить";
			this->clearViewBtn->UseVisualStyleBackColor = true;
			this->clearViewBtn->Click += gcnew System::EventHandler(this, &DLListForm::clearViewBtn_Click);
			// 
			// DLListForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(952, 685);
			this->Controls->Add(this->clearViewBtn);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->outTextBox);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->panel1);
			this->Margin = System::Windows::Forms::Padding(6);
			this->Name = L"DLListForm";
			this->Text = L"Lab3";
			this->Load += gcnew System::EventHandler(this, &DLListForm::DLListForm_Load);
			this->panel1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void DLListForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void groupBox2_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void createBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		this->list = new LinkedList();
		this->outTextBox->AppendText("------New empty queue was created------");
		this->outTextBox->AppendText(Environment::NewLine);
	}
	private: System::Void radioBtnChanged(System::Object^ sender, System::EventArgs^ e) {
		RadioButton^ btn = safe_cast<RadioButton^>(sender);
		this->fromBegin = !this->fromBegin;
		if (this->fromBegin == false) this->outTextBox->AppendText("Working from the end");
		else this->outTextBox->AppendText("Working from the beginning");
		this->outTextBox->AppendText(Environment::NewLine);
	}
	private: System::Void addBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ inputValue = this->inputTextBox->Text;
		std::tuple<bool, int> validationResult = IntValidator(inputValue);
		if (std::get<bool>(validationResult) == true) {
			int value = std::get<int>(validationResult);
			if (this->fromBegin) {
				this->list->push_front(value);
				String^ result("----Added to the begin-----");
				result = (result + value.ToString());
				this->printText(result);
			}
			else {
				this->list->push_back(value);
				String^ result("----Added to the end-----");
				result = (result + value.ToString());
				this->printText("----Added to the end-----" + value.ToString());
			}
		}
	}
	private: System::Void printBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		this->printText("---------------------------");
		if (this->list->length == 0) {
			this->printText("Is empty....");
			this->printText("---------------------------");
			return;
		}
		String^ result;
		if (this->fromBegin)
		{
			for (int i = 0; i < this->list->length; i++) {
				int value = this->list->getAt(i)->data;
				result += value.ToString() + " ";
			}
		}
		else {
			for (int i = list->length - 1; i >= 0; i--) {
				int value = this->list->getAt(i)->data;
				result += value.ToString() + " ";
			}
		}
		this->printText(result);
		this->printText("---------------------------");
	}
	private: System::Void clearBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		delete this->list;
		this->list = new LinkedList();
		this->printText("-----Память освобождена-----");
	}
	private: System::Void exitBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		delete this->list;
		Close();
	}
private: System::Void taskBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	this->list->swapMinMax();
	this->printBtn_Click(sender, e);
}
private: System::Void clearViewBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	this->outTextBox->Clear();
}
};
}
