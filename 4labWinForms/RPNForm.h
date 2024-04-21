#pragma once

#include <msclr/marshal_cppstd.h>
#include <tuple>

#include "Stack.h"

using std::tuple;


namespace My4labWinForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for RPNForm
	/// </summary>
	public ref class RPNForm : public System::Windows::Forms::Form
	{
	public:
		RPNForm(void)
		{
			InitializeComponent();
			char letter = 'a';
			for (int i = 0; i < 26; i++) {
				array<String^>^ row = gcnew array<String^>{System::Char::ToString(letter++), "0.0"};
				gridView->Rows->Add(row);
			}
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RPNForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::TextBox^ RPNBox;
	
	private: String^ RPNResult;

	protected:

	private: System::Windows::Forms::TextBox^ inputBox;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ resultBox;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ calcRPNbtn;

	private: System::Windows::Forms::Button^ toRPNbtn;

	private: System::Windows::Forms::DataGridView^ gridView;


	private: System::Windows::Forms::Button^ clearGrid;


	private: System::Windows::Forms::Label^ errorLabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ nameColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ValueColumn;








	protected:



	protected:

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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->resultBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->calcRPNbtn = (gcnew System::Windows::Forms::Button());
			this->toRPNbtn = (gcnew System::Windows::Forms::Button());
			this->RPNBox = (gcnew System::Windows::Forms::TextBox());
			this->inputBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->gridView = (gcnew System::Windows::Forms::DataGridView());
			this->clearGrid = (gcnew System::Windows::Forms::Button());
			this->errorLabel = (gcnew System::Windows::Forms::Label());
			this->nameColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ValueColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridView))->BeginInit();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->resultBox);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->calcRPNbtn);
			this->panel1->Controls->Add(this->toRPNbtn);
			this->panel1->Controls->Add(this->RPNBox);
			this->panel1->Controls->Add(this->inputBox);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Location = System::Drawing::Point(386, 60);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(664, 318);
			this->panel1->TabIndex = 0;
			// 
			// resultBox
			// 
			this->resultBox->Location = System::Drawing::Point(210, 257);
			this->resultBox->Name = L"resultBox";
			this->resultBox->ReadOnly = true;
			this->resultBox->Size = System::Drawing::Size(100, 31);
			this->resultBox->TabIndex = 7;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(65, 257);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(115, 25);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Результат";
			// 
			// calcRPNbtn
			// 
			this->calcRPNbtn->Location = System::Drawing::Point(455, 142);
			this->calcRPNbtn->Name = L"calcRPNbtn";
			this->calcRPNbtn->Size = System::Drawing::Size(161, 70);
			this->calcRPNbtn->TabIndex = 5;
			this->calcRPNbtn->Text = L"Посчитать";
			this->calcRPNbtn->UseVisualStyleBackColor = true;
			this->calcRPNbtn->Click += gcnew System::EventHandler(this, &RPNForm::calcRPNbtn_Click);
			// 
			// toRPNbtn
			// 
			this->toRPNbtn->Location = System::Drawing::Point(455, 36);
			this->toRPNbtn->Name = L"toRPNbtn";
			this->toRPNbtn->Size = System::Drawing::Size(161, 72);
			this->toRPNbtn->TabIndex = 4;
			this->toRPNbtn->Text = L"Перевести";
			this->toRPNbtn->UseVisualStyleBackColor = true;
			this->toRPNbtn->Click += gcnew System::EventHandler(this, &RPNForm::toRPNbtn_Click);
			// 
			// RPNBox
			// 
			this->RPNBox->Location = System::Drawing::Point(40, 190);
			this->RPNBox->Name = L"RPNBox";
			this->RPNBox->ReadOnly = true;
			this->RPNBox->Size = System::Drawing::Size(270, 31);
			this->RPNBox->TabIndex = 3;
			// 
			// inputBox
			// 
			this->inputBox->Location = System::Drawing::Point(40, 77);
			this->inputBox->Name = L"inputBox";
			this->inputBox->Size = System::Drawing::Size(270, 31);
			this->inputBox->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(65, 142);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(182, 25);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Полученная ОПЗ";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(65, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(214, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Введите выражение";
			// 
			// gridView
			// 
			this->gridView->AllowUserToAddRows = false;
			this->gridView->AllowUserToDeleteRows = false;
			this->gridView->AllowUserToResizeColumns = false;
			this->gridView->AllowUserToResizeRows = false;
			this->gridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->nameColumn,
					this->ValueColumn
			});
			this->gridView->Location = System::Drawing::Point(2, 60);
			this->gridView->Name = L"gridView";
			this->gridView->RowHeadersVisible = false;
			this->gridView->RowHeadersWidth = 82;
			this->gridView->RowTemplate->Height = 33;
			this->gridView->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->gridView->Size = System::Drawing::Size(368, 544);
			this->gridView->TabIndex = 1;
			// 
			// clearGrid
			// 
			this->clearGrid->Location = System::Drawing::Point(426, 523);
			this->clearGrid->Name = L"clearGrid";
			this->clearGrid->Size = System::Drawing::Size(179, 81);
			this->clearGrid->TabIndex = 2;
			this->clearGrid->Text = L"Clear Grid";
			this->clearGrid->UseVisualStyleBackColor = true;
			this->clearGrid->Click += gcnew System::EventHandler(this, &RPNForm::clearGrid_Click);
			// 
			// errorLabel
			// 
			this->errorLabel->AutoSize = true;
			this->errorLabel->Location = System::Drawing::Point(421, 442);
			this->errorLabel->Name = L"errorLabel";
			this->errorLabel->Size = System::Drawing::Size(0, 25);
			this->errorLabel->TabIndex = 3;
			// 
			// nameColumn
			// 
			this->nameColumn->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->nameColumn->Frozen = true;
			this->nameColumn->HeaderText = L"Имя";
			this->nameColumn->MinimumWidth = 10;
			this->nameColumn->Name = L"nameColumn";
			this->nameColumn->ReadOnly = true;
			this->nameColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// ValueColumn
			// 
			this->ValueColumn->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->ValueColumn->HeaderText = L"Знач.";
			this->ValueColumn->MinimumWidth = 10;
			this->ValueColumn->Name = L"ValueColumn";
			this->ValueColumn->Width = 250;
			// 
			// RPNForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1092, 648);
			this->Controls->Add(this->errorLabel);
			this->Controls->Add(this->clearGrid);
			this->Controls->Add(this->gridView);
			this->Controls->Add(this->panel1);
			this->Name = L"RPNForm";
			this->Text = L"RPNForm";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void clearGrid_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 0; i < 26; i++)
		{
			this->gridView->Rows[i]->Cells[1]->Value = "0";
		}
	}
	private: System::Void toRPNbtn_Click(System::Object^ sender, System::EventArgs^ e) {
		this->errorLabel->Text = "";
		if (this->inputBox->Text == "") {
			this->errorLabel->Text = "[Error] Input is empty!";
			return;
		}
		string input = msclr::interop::marshal_as<std::string>(this->inputBox->Text);
		string result = infixToRPN(input);
		this->RPNResult = msclr::interop::marshal_as<System::String^>(result);
		this->RPNBox->Text = RPNResult;
	}

	private: System::Void calcRPNbtn_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			string expression = msclr::interop::marshal_as<std::string>(this->RPNBox->Text);
			vector<tuple<char, double>> values;
			for (int i = 0; i < 26; i++) {
				if (this->RPNResult->Contains(this->gridView->Rows[i]->Cells[0]->Value->ToString())) {
					std::string letterFromTable = msclr::interop::marshal_as<std::string>(this->gridView->SelectedRows[i]->Cells[0]->Value->ToString());
					double value = System::Double::Parse(this->gridView->SelectedRows[i]->Cells[1]->Value->ToString());
					values.push_back(std::tuple<char, double>(letterFromTable[0], value));
				}
			}
			double result = evaluateRPN(expression, values);
			this->resultBox->Text = result.ToString();
		}
		catch (Exception^ e) {
			this->errorLabel->Text = e->Message;
		}
	}
};
}
