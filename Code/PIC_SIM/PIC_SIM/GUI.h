#pragma once

using namespace System;
using namespace System::Windows::Forms;

void but1_click(TextBox^ textBox1, TextBox^ textBox2, TextBox^ textBox3 ) {
	int x = Convert::ToInt32(textBox1->Text);
	int y = Convert::ToInt32(textBox2->Text);

	int erg = add(x, y);

	textBox3->AppendText(String::Format("Summe={0}\n", erg));
}