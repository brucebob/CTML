/*
	CTML - written by Tinfoilboy
	uses the MIT License (https://github.com/tinfoilboy/CFML/blob/master/LICENSE)
*/
#pragma once
#include "Node.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace CTML {
	class Document {
		// the doctype of this document
		Node m_doctype;
		// the head tag of this document
		Node m_head;
		// the body tag of this document
		Node m_body;
	public:
		// the default constructor for a document
		Document() {
			// create and set the doctype to html
			this->m_doctype = Node("", "html");
			this->m_doctype.SetType(DOCUMENT_TYPE);
			// create the head tag
			this->m_head = Node("head");
			// create the body tag
			this->m_body = Node("body");
		}

		// add a node to the head element
		void AddNodeToHead(Node node) {
			this->m_head.AppendChild(node);
		}

		// add a node to the body element
		void AddNodeToBody(Node node) {
			this->m_body.AppendChild(node);
		}

		// gets the current document as a string
		const std::string ToString(const Readability& readability) {
			bool isMultiline = (readability == MULTILINE || readability == MULTILINE_BR);
			std::string doc = "";
			// add the doctype to the string
			doc += m_doctype.ToString(readability, 0);
			// every document needs an html tag, add it
			doc += "<html>";
			// if we want readability, append a newline to the html beginning tag
			doc += ((isMultiline) ? "\n" : "");
			// append the head tag and its children
			doc += m_head.ToString(readability, 1) + ((isMultiline) ? "\n" : "");
			// append the body tag and its children
			doc += m_body.ToString(readability, 1) + ((isMultiline) ? "\n" : "");
			// close the html tag
			doc += "</html>";
			return doc;
		}

		// get the current document as a tree represented in a string
		const std::string ToTree() {
			std::string treeStr = "";
			treeStr += "html\n";
			treeStr += m_head.GetTreeString(0);
			treeStr += m_body.GetTreeString(0);
			return treeStr;
		}

		// write the current document to a file
		bool WriteToFile(std::string filePath, const Readability& readability) {
			std::ofstream file = std::ofstream(filePath);
			if (file.is_open()) {
				file << this->ToString(readability);
				file.close();
				return true;
			}
			return false;
		}
	};
}