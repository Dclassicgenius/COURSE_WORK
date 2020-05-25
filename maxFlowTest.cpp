#include "pch.h"
#include "CppUnitTest.h"
#include"../Flow/Flow.h"
#include <fstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MaxFlowTests
{
	TEST_CLASS(MaxFlowTests)
	{
	public:
		Assert assert;
		TEST_METHOD(Correct_input_for_6_vertexes)
		{
			ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text1.txt");
			Flow flow(textInput);
			assert.AreEqual(flow.max_flow(), 5);
		}
		TEST_METHOD(TestMethod_Exception_entering_the_first_character) {
			try {
				ifstream textIinput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text2.txt");
				Flow flow(textIinput);
			}
			catch (exception& error) {
				assert.AreEqual(error.what(), "Error entering the first character in the string or missing a space after it.  ");
			}
		}
		TEST_METHOD(Exception_entering_the_second_character) {
			try {
				ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text3.txt");
				Flow flow(textInput);
			}
			catch (exception& error) {
				assert.AreEqual(error.what(), "Error entering the second character in the string or missing a space after it. ");
			}
		}
		TEST_METHOD(Exception_entering_the_third_character) {
			try {
				ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text4.txt");
				Flow flow(textInput);
			}
			catch (exception& error) {
				assert.AreEqual(error.what(), "Error entering the third character in the string, the presence of a space after it or a negative number. ");
			}
		}
		TEST_METHOD(Exception_empty_string) {
			try {
				ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text5.txt");
				Flow flow(textInput);
			}
			catch (exception& error) {
				assert.AreEqual(error.what(), "A data-entry error. Check the correctness of the input in the file. ");
			}
		}
		TEST_METHOD(Correct_output_for_6_vertexes_)
		{
			ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text6.txt");
			Flow flow(textInput);
			assert.AreEqual(flow.max_flow(), 25);
		}
		TEST_METHOD(Correct_output_for_2_vertexes)
		{
			ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text7.txt");
			Flow flow(textInput);
			assert.AreEqual(flow.max_flow(), 20);
		}
		TEST_METHOD(Exception_path_from_vertex_to_itself) {
			try {
				ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text8.txt");
				Flow flow(textInput);
			}
			catch (exception& error) {
				assert.AreEqual(error.what(), "There is a path from the vertex to itself. ");
			}
		}
		TEST_METHOD(Correct_output_for_20_vertexes)
		{
			ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text9.txt");
			Flow flow(textInput);
			assert.AreEqual(flow.max_flow(), 19);
		}
		TEST_METHOD(Exception_negative_number_in_the_input) {
			try {
				ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text10.txt");
				Flow flow(textInput);
			}
			catch (exception& error) {
				assert.AreEqual(error.what(), "Error entering the third character in the string, the presence of a space after it or a negative number. ");
			}
		}
		TEST_METHOD(Exception_missing_sink) {
			try {
				ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text11.txt");
				Flow flow(textInput);
			}
			catch (exception& error) {
				assert.AreEqual(error.what(), "Sink is missing");
			}
		}
		TEST_METHOD(Exception_missing_source) {
			try {
				ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text12.txt");
				Flow flow(textInput);
			}
			catch (exception& error) {
				assert.AreEqual(error.what(), "Source is missing");
			}
		}
		TEST_METHOD(Exception_two_different_connectivity_components) {
			try {
				ifstream textInput("C:\\Users\\DCLASSICGENIUS\\source\\repos\\Flow\\maxFlowTest\\Text13.txt");
				Flow flow(textInput);
			}
			catch (exception& error) {
				assert.AreEqual(error.what(), "There is no way from the source to the sink");
			}
		}
	};
}
