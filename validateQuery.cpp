#include "validateQuery.h"
bool isAlphaCheck(std::string s) {
	bool check = true;
	for (int i = 0; i < s.length(); i++) {
		if (!(s[i] >= 65 && s[i] <= 90) && !(s[i] >= 97 && s[i] <= 122)) {
			check = false;
			std::cout << "Error, column or table name cannot contain any special character." << std::endl;
		}
	}
	return check;

}

bool isDataTypeCheck(std::string s) {
	if (s == "string" || s == "char" || s == "varchar" || s == "text" || s == "bool" || s == "int" || s == "float" || s == "datetime" || s == "date" || s == "year" || s == "time" || s == "timestamp") {
		return true;
	}
	return false;
}
bool isAvailable(std::string s) {
	if (s == "create" || s == "drop" || s == "table" || s == "insert" || s == "alter" || s == "update" || s == "order" || s == "having" || s == "not" || s == "null" || s == "references" || s == "on" || s == "use" || s == "delete" || s == "by" || s == "desc" || s == "asc" || s == "group" || s == "distinct" || s == "from" || s == "limit" || s == "where" || s == "in" || s == "like" || s == "values" || s == "into" || isDataTypeCheck(s)) {
		return false;
	}
	return true;
}


bool isdigit(std::string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] < 48 || s[i] > 57) {
			return false;
		}
	}
	return true;
}
std::string getDataType(std::string s1) {
	std::string type = typeid(std::stof(s1)).name();

	if (isdigit(s1)) {
		return "int";
	}
	else if (!isdigit(s1) && ((s1 == "true" || s1 == "false") || (s1 == "True" || s1 == "False") || (s1 == "TRUE" || s1 == "FALSE"))) {
		return "bool";
	}
	else if (isAlphaCheck(s1) && s1.length() > 1) {
		return "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >";
	}
	else if (isAlphaCheck(s1)) {
		return "char";
	}
	else if (type == "f") {
		return "float";
	}
	else {
		return "---";
	}


}
validateQuery::validateQuery() {
	createCheck = false;
	insertCheck = false;
	pkeyCheck = false;;
	fkeyCheck = false;
	selectCheck = false;
	whereCheck = false;
	orderCheck = false;
	joinCheck = false;
	deleteCheck = false;
	updateCheck = false;
	alterCheck = false;
	dropTableCheck = false;
}
bool validateQuery::validate(std::vector<std::string> v1) {
	std::pair<std::string, std::string> temp1;
	bool pcheck = false;
	int fkCount = 0;
	std::string foreignKey;
	std::vector<std::pair<std::string, std::string>> temp;
	bool check = true;
	bool check2 = false;
	int num = 0;
	int a = 0;
	int count = 0;
	std::pair<std::string, std::string> column;
	for (int i = 0; i < v1.size(); i++) {

		if (v1[i] == "") {
			v1.pop_back();
		}
	}

	std::vector<std::string> v1Copy = v1;

	for (int i = 0; i < v1.size(); i++) {
		std::transform(v1[i].begin(), v1[i].end(), v1[i].begin(), ::tolower);
	}

	for (int i = 0; i < v1.size(); i++) {
		try {
			if (v1.at(i) + v1.at(i + 1) == "createtable" && isAlphaCheck(v1.at(i + 2)) && v1.at(i + 2) != "(" && v1.at(i + 3) == "(") {

				query.first = v1Copy.at(i + 2);
				a = i + 4;
				while (v1[a] != ")") {
					if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && isDataTypeCheck(v1.at(a + 1))) {

						if (v1Copy.at(a + 1) == "string" || v1Copy.at(a + 1) == "varchar") {
							v1Copy.at(a + 1) = "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >";
						}

						column.first = v1Copy.at(a + 1); 
						column.second = v1Copy.at(a);

						query.second.push_back(column);
						createCheck = true;
						count++;
						if (v1.at(a + 2) == ",") {

							a += 3;


						}
						else if (v1.at(a + 2) == ")") {

							a += 2;

						}



						else if (v1.at(a + 2) + v1.at(a + 3) == "primarykey") {
							keys["pk"] = v1Copy[a];
							pkeyCheck = true;
							if (v1.at(a + 4) == ",") {

								a += 5;
							}
							else if (v1.at(a + 4) == ")") {

								a += 4;
							}
							else {
								check = false;
								break;
							}


						}
						else if (v1.at(a + 2) + v1.at(a + 3) + v1.at(a + 4) == "foreignkeyreferences" && isAlphaCheck(v1.at(a + 5)) && !isDataTypeCheck(v1.at(a + 5)) && v1.at(a + 6) == "(" && isAlphaCheck(v1.at(a + 7)) && v1.at(a + 8) == ")") {
							foreignKey = foreignKey + "fk" + std::to_string(fkCount);
							keys[foreignKey] = v1Copy.at(a);
							fkeyCheck = true;
							foreignKey.clear();
							fkCount++;
							if (v1.at(a + 9) == ",") {

								a += 10;
							}
							else if (v1.at(a + 9) == ")") {

								a += 9;
							}
							else {
								check = false;
								break;
							}
						}


						else {
							check = false;
							break;
						}

					}
					else {
						check = false;
						break;
					}

				}

				if (v1.at(a + 1) == ";") {
					check = true;
					a++;

				}
				else {
					check = false;
				}


				i += a;


			}
			else if (v1.at(i) + v1.at(i + 1) == "insertinto" && isAlphaCheck(v1.at(i + 2)) && isAvailable(v1.at(i + 2)) && v1.at(i + 3) == "values")
			{
				a = 0;
				a = i + 4;
				int counter = 0;
				std::pair<std::string, std::string> p1;
				InsertQuery.first = v1Copy.at(i + 2);
				while (v1.at(a) != ";") {
					std::string s1;
					if (v1.at(a) == "(") {
						counter = a + 1;

						while (v1.at(counter) != ")") {

							if (v1.at(counter) != ",") {

								if (v1.at(counter) == "'") {
									/*counter++;
									v1Copy.at(counter).erase(remove_if(v1Copy.at(counter).begin(), v1Copy.at(counter).end(), ::isspace),
										v1Copy.at(counter).end());
									v1.at(counter).erase(remove_if(v1.at(counter).begin(), v1.at(counter).end(), ::isspace),
										v1.at(counter).end());*/
									s1 = s1 + v1Copy.at(++counter);
									while (v1Copy.at(++counter) != "'") {
										s1 = s1 + v1Copy.at(counter);
									}

									if (isAlphaCheck(s1) || isdigit(s1)) {
										p1.first = ((s1 == "true" || s1 == "false") || (s1 == "True" || s1 == "False") || (s1 == "TRUE" || s1 == "FALSE")) ? "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >" : getDataType(s1);
										p1.second = s1;
										check2 = true;
									}


								}
								else {

									if (isAlphaCheck(v1.at(counter)) || isdigit(v1.at(counter))) {
										p1.first = getDataType(v1.at(counter));
										p1.second = v1Copy.at(counter);
										check2 = true;
									}


								}

								if (check2) {
									temp.push_back(p1);
								}
								check2 = false;
								for (int i = 0; i < temp.size(); i++) {

								}

								s1.clear();


							}

							counter++;
						}

						InsertQuery.second.push_back(temp);
						insertCheck = true;

						temp.clear();
						if (v1.at(counter + 1) == ";") {
							a = counter + 1;
						}
						else if (v1.at(counter + 1) == ",") {
							a = counter + 2;
						}
						else {
							check = false;
							break;
						}


						counter = 0;

					}
					else {
						check = false;
						break;
					}

				}

				i += a;

			}
			else if (v1.at(i) == "select" || v1.at(i) == "delete" || v1.at(i) == "update") {

				a = 0;
				a = i + 1;
				int b = 0;
				while (v1.at(a) != ";" && check != false) {
					if (v1.at(a) == "*") {
						selectQuery.second.push_back(v1Copy.at(a));
						a++;
					}
					else if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && v1.at(a - 1) == "select") {
						b = a;

						while (v1.at(b) != "from") {
							if (v1.at(b) == ",") {
								if (v1.at(b + 1) == "from") {
									check = false;
									break;
								}
								else {

									b += 1;
								}

							}
							else if (isAlphaCheck(v1.at(b)) && !isDataTypeCheck(v1.at(b)) && v1.at(b + 1) == "(" && ((isAlphaCheck(v1.at(b + 2)) && !isDataTypeCheck(v1.at(b + 2))) || v1.at(b + 2) == "*") && v1.at(b + 3) == ")") {
								std::string function = v1Copy.at(b) + v1Copy.at(b + 1) + v1Copy.at(b + 2) + v1Copy.at(b + 3);
								if (num > 0 && v1.at(b - 1) != "," && v1.at(b + 4) != "from") {
									check = false;
									break;
								}
								selectQuery.second.push_back(function);
								selectCheck = true;

								b += 4;
								num++;

							}
							else if (isAlphaCheck(v1.at(b)) && !isDataTypeCheck(v1.at(b))) {
								if (num > 0 && v1.at(b - 1) != "," && v1.at(b + 1) != "from") {
									check = false;
									break;
								}
								selectQuery.second.push_back(v1Copy.at(b));
								selectCheck = true;

								b += 1;
								num++;
							}
							else {
								check = false;
								break;
							}



						}

						a = b;


					}
					else if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && v1.at(a - 1) == "update") {
						updateQuery.first = v1Copy.at(a);
						std::pair<std::string, std::string> p;
						if (v1.at(a + 1) == "set") {
							a += 2;
							while (v1.at(a) != ";" && v1.at(a) != "where") {
								if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && v1.at(a + 1) == "=" && isdigit(v1.at(a + 2))) {
									p.first = v1Copy.at(a);
									p.second = v1Copy.at(a + 2);
									updateQuery.second.push_back(p);
									a += 3;
									updateCheck = true;

								}
								else if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && v1.at(a + 1) == "=" && v1.at(a + 2) == "'" && isAlphaCheck(v1.at(a + 3)) && !isDataTypeCheck(v1.at(a + 3)) && v1.at(a + 4) == "'") {
									p.first = v1Copy.at(a);
									p.second = v1Copy.at(a + 3);
									updateQuery.second.push_back(p);
									a += 5;
									updateCheck = true;
								}
								else {
									check = false;
									break;
								}
								if (v1.at(a) != "where" && v1.at(a) != ";") {
									if (v1.at(a) != ",") {

										check = false;
										break;
									}
									else {
										a++;
									}
								}
							}
						}

					}
					else if (v1.at(a) == "from" && v1.at(a - 1) == "delete") {
						if (isAlphaCheck(v1.at(a + 1)) && !isDataTypeCheck(v1.at(a + 1))) {
							deleteQuery = v1Copy.at(a + 1);
							a += 2;
							deleteCheck = true;
						}
						else {
							check = false;
							break;
						}
					}
					else if (v1.at(a) == "from") {
						if (isAlphaCheck(v1.at(a + 1)) && !isDataTypeCheck(v1.at(a + 1))) {
							selectQuery.first = v1Copy.at(a + 1);
							selectCheck = true;
							a += 2;

						}
						else {
							check = false;
							break;
						}
					}
					else if (v1.at(a) == "where") {
						std::tuple<std::string, std::string, std::string> tupleTemp;

						a++;
						while (v1.at(a) != ";") {

							if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a))) {

								if (v1.at(a + 1) + v1.at(a + 2) == "!=" || v1.at(a + 1) + v1.at(a + 2) == "<=" || v1.at(a + 1) + v1.at(a + 2) == ">=") {

									if (isdigit(v1.at(a + 3))) {
										tupleTemp = make_tuple(v1Copy.at(a), v1Copy.at(a + 1) + v1Copy.at(a + 2), v1Copy.at(a + 3));
										whereSelect.push_back(tupleTemp);
										whereCheck = true;
										a += 4;
									}
									else if (v1.at(a + 3) == "'" && isAlphaCheck(v1.at(a + 4)) && v1.at(a + 5) == "'") {
										tupleTemp = make_tuple(v1Copy.at(a), v1Copy.at(a + 1) + v1Copy.at(a + 2), v1Copy.at(a + 4));
										whereSelect.push_back(tupleTemp);
										whereCheck = true;
										a += 6;
									}
									else {
										check = false;
										break;
									}
								}
								else if (v1.at(a + 1) == "=" || v1.at(a + 1) == "<" || v1.at(a + 1) == ">") {

									if (isdigit(v1.at(a + 2))) {
										tupleTemp = make_tuple(v1Copy.at(a), v1Copy.at(a + 1), v1Copy.at(a + 2));
										whereSelect.push_back(tupleTemp);
										whereCheck = true;
										a += 3;
									}
									else if (v1.at(a + 2) == "'" && isAlphaCheck(v1.at(a + 3)) && v1.at(a + 4) == "'") {
										tupleTemp = make_tuple(v1Copy.at(a), v1Copy.at(a + 1), v1Copy.at(a + 3));
										whereSelect.push_back(tupleTemp);
										whereCheck = true;
										a += 5;
									}


									else {
										check = false;
										break;
									}
								}

								else {
									check = false;
									break;
								}

								if (v1.at(a) == "and") {
									a++;
								}
							}
						}

					}
					else if (v1.at(a) + v1.at(a + 1) == "orderby") {
						if (isAlphaCheck(v1.at(a + 2)) && !isDataTypeCheck(v1.at(a + 2)) && (v1.at(a + 3) == "asc" || v1.at(a + 3) == "desc")) {
							orderSelect.first = v1Copy.at(a + 2);
							orderSelect.second = v1Copy.at(a + 3);
							orderCheck = true;
							a += 4;
						}
						else {
							check = false;
							break;
						}
					}
					else if (v1.at(a) == "join") {

						temp1.first = v1Copy.at(a - 1);
						if (isAlphaCheck(v1.at(a + 1)) && !isDataTypeCheck(v1.at(a + 1)) && v1.at(a + 2) == "on") {

							temp1.second = v1Copy.at(a + 1);
							if (isAlphaCheck(v1.at(a + 3)) && !isDataTypeCheck(v1.at(a + 3)) && v1.at(a + 4) == "." && isAlphaCheck(v1.at(a + 5)) && !isDataTypeCheck(v1.at(a + 5)) && v1.at(a + 6) == "=" && isAlphaCheck(v1.at(a + 7)) && !isDataTypeCheck(v1.at(a + 7)) && v1.at(a + 8) == "." && isAlphaCheck(v1.at(a + 9)) && !isDataTypeCheck(v1.at(a + 9))) {

								joinSelect.first = temp1;

								if (v1.at(a + 3) != temp1.first || v1.at(a + 7) != temp1.second) {
									check = false;
									break;
								}
								temp1.first = v1Copy.at(a + 5);
								temp1.second = v1Copy.at(a + 9);
								joinSelect.second = temp1;
								joinCheck = true;
								a += 10;
							}
							else {
								check = false;
								break;
							}
						}
						else {
							check = false;
							break;
						}
					}
					else {
						check = false;
						break;
					}
				}

				i += a;

			}
			else if (v1.at(i) + v1.at(i + 1) == "altertable" && isAlphaCheck(v1.at(i + 2)) && !isDataTypeCheck(v1.at(i + 2))) {

				a = i + 3;
				alterQuery.first = v1Copy.at(i + 2);
				std::pair<std::string, std::string> p;
				if (v1.at(a) == "add") {

					a++;
					if (v1.at(a) == "(") {
						a++;
						pcheck = true;


					}
					while (v1.at(a) != ";") {

						if (pcheck) {

							if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && isDataTypeCheck(v1.at(a + 1))) {

								p.first = v1Copy.at(a + 1);
								p.second = v1Copy.at(a);
								alterQuery.second.push_back(p);
								alterCheck = true;
								a += 2;

							}
							else {
								check = false;
								break;
							}
							if (v1.at(a) != ")") {
								if (v1.at(a) != ",") {
									check = false;
									break;
								}
								else {
									a++;
								}
							}
							else {
								a++;
								pcheck = false;
								if (v1.at(a) != ";") {
									check = false;
									break;
								}
							}
						}
						else if (isAlphaCheck(v1.at(a)) && !isDataTypeCheck(v1.at(a)) && isDataTypeCheck(v1.at(a + 1))) {

							p.first = v1Copy.at(a + 1);
							p.second = v1Copy.at(a);
							alterQuery.second.push_back(p);
							alterCheck = true;
							a += 2;
							if (v1.at(a) != ";") {
								check = false;
								break;
							}
						}
						else {
							check = false;
							break;
						}


					}
				}
				else if (v1.at(a) + v1.at(a + 1) == "dropcolumn") {

					if (isAlphaCheck(v1.at(a + 2)) && !isDataTypeCheck(v1.at(a + 2)) && v1.at(a + 3) == ";") {
						p.first = "drop";
						p.second = v1Copy.at(a + 2);
						alterQuery.second.push_back(p);
						alterCheck = true;
						a += 4;
					}
					else {
						check = false;
						break;
					}
				}
				else if (v1.at(a) + v1.at(a + 1) == "renamecolumn") {

					if (isAlphaCheck(v1.at(a + 2)) && !isDataTypeCheck(v1.at(a + 2)) && v1.at(a + 3) == "to" && isAlphaCheck(v1.at(a + 4)) && !isDataTypeCheck(v1.at(a + 4)) && v1.at(a + 5) == ";") {
						p.first = "rename";
						p.second = v1Copy.at(a + 2) + '~' + v1Copy.at(a + 4);
						alterQuery.second.push_back(p);
						alterCheck = true;
						a += 6;
					}
					else {
						check = false;
					}
				}
				i += a;
			}
			else if (v1.at(a) + v1.at(a + 1) == "droptable") {

				if (isAlphaCheck(v1.at(a + 2)) && !isDataTypeCheck(v1.at(a + 2)) && v1.at(a + 3) == ";") {
					dropTableQuery = v1.at(a + 2);
					dropTableCheck = true;
					a += 4;
				}
				else {
					check = false;
					break;
				}
				i += a;
			}
			else {
				check = false;
				std::cout << "Invalid query(potential logic error)." << std::endl;
				break;
			}
		}
		catch (...) {
			std::cout << "Invalid query(Out of bounds error, potential syntax error)." << std::endl;
			check = false;
			break;
		}

	}

	return check;
}