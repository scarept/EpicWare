#include "CreateStatement.h"


CCreateStatement::CCreateStatement(){}


CCreateStatement::~CCreateStatement(){}

void CCreateStatement::assertData(vector<Word> *stats){
	vector<Word> newVector = *stats;
	Word temp_word; //= {"","",""};
	while (!newVector.empty()){
		strcpy(temp_word.text,stats->end()->text);
		strcpy(temp_word.topic, stats->end()->topic);
		strcpy(temp_word.language, stats->end()->language);

		joinConnection(temp_word.text, temp_word.topic, temp_word.language);
		
		newVector.pop_back();
	}
}

void CCreateStatement::joinConnection(char *text, char *category, char *language){
	PlTermv term(2);
	PlTermv stats(text, category, language);
	term[0] = PlCompound("word", stats);
	cout << (char *)term[0] << endl;
	PlQuery query("asserta", term);
	query.next_solution();
}