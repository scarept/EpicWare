typedef struct{
	int l;
	int c;
} Cordenadas;

class TicTacToeLogic{

public:
	void addBase(char c);
	void addAllBase(char *arr);
	void assertData();
	Cordenadas fastestWayAvailable();
	int validaJogada(int player, int l, int c);
	int jogadaJogador(int l, int c);
	int jogadaComputador()
};