/* User.cpp */
/* Classe que representa um Usuario */
#include "User.h"

/* Construtores */
//--------------------------------------------------------------------------
User::User() {}

User::User(int _id) { id = _id; }

/* Metodos set */
//--------------------------------------------------------------------------
void User::setId(int _id){ id = _id; }

void User::setKindOfUser(string _kindOfUser){ kindOfUser = _kindOfUser; }

void User::setName(string _name){ name = _name; }

void User::setAge(int _age){ age = _age; }

void User::setGender(string _gender){ gender = _gender; }

/* Metodos get */
//--------------------------------------------------------------------------
int User::getId(){ return id; }

string User::getkindOfUser(){ return kindOfUser; }

string User::getName(){ return name; }

int User::getAge(){ return age; }

string User::getGender(){ return gender; }

list<MusicTrack> User::getPlayList(){ return playList; }

/* Outros Metodos */
//--------------------------------------------------------------------------
/*
	-Metodo showUserInformation() exibe no ecra os campos do usuario;
	-parametro optDisplay: indica a quantidade de campos que serao mostrados (ordem sequencial)
	-Ex: optDisplay=2 exibe apenas o id e o kindOfUser
*/
void User::showUserInformation(int optDisplay)
{
	cout << endl;
	for(int i=0 ; i<optDisplay ; i++){
		switch(i){
			case 0:
				cout << "\nID:\t" << id;
			break;
			case 1:
				cout << "\nKind:\t"  << kindOfUser;
				if(kindOfUser=="a")
					cout << "dministrator";
				else
					cout << "ormal";
			break;
			case 2:
				cout << "\nName:\t" << name;
			break;
			case 3:
				cout << "\nAge:\t" << age;
			break;
			case 4:
				cout << "\nGender:\t"  << gender;
			break;
			default:
				return;
			break;
		}
	}
	cout << endl;
}

/*
	-Metodo loadPlaylist() carrega no programa as informacoes do usuario;
	-Nome do ficheiro: "playListUserXXX.csv" onde XXX indica o id do usuario;
	-As informacoes sao referentes as musicas contidas na playlist do usuario XXX,
	 uma por linha, com campos separados por virgula.
*/
void User::loadPlaylist(){
	stringstream fileName;
	fileName << "playListUser" << id << ".csv";
	string fileNameAux = fileName.str();
	ifstream fin;
	fin.open(fileNameAux);
	if(fin.fail()){
		fin.close();
//		cout << "\nFailure to open file 'playListUserXXX.csv' " << endl; //error
		return;
	}
	stringstream fieldWriter;
	string lineContent, Field;
	int commaPosition = 0;
	int beginOfSubstring = 0;
	bool createNewMusic = true;
	int intField = 0;
	MusicTrack newMusic(intField);
	int fillFieldControl = 0;
	while(getline(fin, lineContent)){
		if(lineContent[0] != 'I'){
			while(commaPosition != -1){
				commaPosition = lineContent.find_first_of(',',commaPosition + 1);
				if(createNewMusic){
					Field = lineContent.substr(beginOfSubstring, commaPosition - beginOfSubstring);
					intField = atoi(Field.c_str());
					createNewMusic = false;
					newMusic.setId(intField);
				}
				else{
					Field = lineContent.substr(beginOfSubstring, commaPosition - beginOfSubstring);
					switch(fillFieldControl){
						case 0:
							newMusic.setTitle(Field);
							break;
						case 1:
							newMusic.setArtist(Field);
							break;
						case 2:
							newMusic.setAuthor(Field);
							break;
						case 3:
							newMusic.setAlbum(Field);
							break;
						case 4:
							newMusic.setMusicGenre(Field);
							break;
						case 5:
							intField = atoi(Field.c_str());
							newMusic.setYear(intField);
							break;
						case 6:
							intField = atoi(Field.c_str());
							newMusic.setNumberOfLikes(intField);
							break;
						case 7:
							intField = atoi(Field.c_str());
							newMusic.setNumberOfDislikes(intField);
							break;
						default:
							break;
					}
					fillFieldControl++;
				}
				if(commaPosition != -1){
					beginOfSubstring = commaPosition + 1;
				}
			}
			playList.push_back(newMusic);
			commaPosition = 0;
			beginOfSubstring = 0;
			createNewMusic = true;
			fillFieldControl = 0;
		}
	}
	fin.close();
}

/*
	-Metodo managePlaysList() gerencia as opcoes de adicionar/remover musicas na playlist;
	-parametro listOfMusicTrack: lista de musicas da RadioStation;
	-Permanece no menu ate' que o usuario deseje sair.
*/
void User::managePlaysList(list<MusicTrack> &listOfMusicTrack)
{
	int choice, numMusic, idMus;
	if(listOfMusicTrack.empty()){
		cout << "\n\n<<The Radio Station do not have any music!>>\n";
		return;
	}
	while(true){
		cout << "\n[1] Add Music" << endl;
		cout << "[2] Remove Music" << endl;
		cout << "[9] Exit" << endl;
		choice = Utilities::readInt("\nType your choose: ",1,9);
		switch(choice)
		{
			case 1:
				numMusic = showMusics(listOfMusicTrack);
				idMus = Utilities::readInt("\nWhich music do you want to add[ID]?: ",1,numMusic);
				addMusic(listOfMusicTrack, idMus);
				updatePlaylistUserFile(listOfMusicTrack);
			break;
			case 2:
				if(playList.empty()){
					cout << "\n<<Playlist empty!>>\n";
					break;
				}
				showPlaylist();
				cout << "\nWhich music do you want to remove[ID]?: " << endl;
				idMus = idPlayListRemove();
				removeMusic(idMus);
				updatePlaylistUserFile(listOfMusicTrack);
			break;

			case 9:
				cout << "\Exit..." << endl;
				return;
			default:
				cout << "\nPlease, type a valid number!" << endl;
			break;
		}
		cout << endl;
	}
}

/*
	-Metodo showMusics() exibe no ecra as musicas disponiveis na RadioStation;
	-parametro listOfMusicTrack: lista de musicas da RadioStation;
	-Retorna um int indicando o id mais elevado da lista acima 
	 (para efeito de tratamento de entrada de dados).
*/
int User::showMusics(list<MusicTrack> &listOfMusicTrack)
{
	int maxId=0;
	list<MusicTrack>::iterator mus;
	for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++){
		(*mus).showMusicInformation(2);
		if((*mus).getId() > maxId)
			maxId = (*mus).getId();
	}
	return maxId;
}

/*
	-Metodo addMusic() adiciona para a playlist do usuario a musica com idOption;
	-parametro listOfMusicTrack: lista de musicas da RadioStation;
	-parametro idOption: id da musica que o usuario decidiu acrescentar a sua playlist.
	-Caso a musica assinalada exista na RadioStation e ainda nao esteja na playlist
	 do usuario, este e' adicionada na playlist.
*/
void User::addMusic(list<MusicTrack> &listOfMusicTrack, int idOption)
{
	list<MusicTrack>::iterator mus;
	for(mus = playList.begin(); mus != playList.end(); mus++){
		if(idOption == (*mus).getId()){
			cout << "\n\n<<This music is already in your play List!>>" << endl;
			return;
		}
	}
	for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++){
		if((*mus).getId() == idOption){
			cout << "\n << Music " << (*mus).getTitle() << " added in your playlist!>>\n" << endl;
			playList.push_back((*mus));
		}	
	}
}

/*
	-Metodo updatePlaylistUserFile() atualiza o ficheiro do usuario XXX;
	-parametro listOfMusicTrack: lista de musicas da RadioStation;
	-Sobrescreve as informacoes do ficheiro baseado no atributo playlist do usuario.
*/
void User::updatePlaylistUserFile(list<MusicTrack> &listOfMusicTrack)
{
	vector<int> ids;
	ifstream fin;
	ofstream fout;
	string s;
	stringstream filename, info;
	list<MusicTrack>::iterator pl;

	for(pl = playList.begin(); pl != playList.end(); pl++)
		ids.push_back((*pl).getId());
	
	playList.clear();
	for(pl = listOfMusicTrack.begin(); pl != listOfMusicTrack.end(); pl++){
		for(int i=0 ; i<ids.size() ; i++){
			if((*pl).getId() == ids[i] && !idInPlayList(ids[i])){
			info << (*pl).getId() << "," << (*pl).getTitle() << "," << (*pl).getArtist() << "," << (*pl).getAuthor() << "," 
				 << (*pl).getAlbum() << "," << (*pl).getMusicGenre() << "," << (*pl).getYear() << "," << (*pl).getNumberOfLikes() << ","
				 << (*pl).getNumberOfDislikes() << "\n";
			playList.push_back((*pl));
			}
		}
	}
	filename << "playListUser" << id << ".csv";
	fin.open(filename.str());
	if(fin.fail() && playList.empty())
		return;
	fout.open(filename.str());
	fout << info.str();
	fout.close();
	fin.close();
}

/*
	-Metodo showPlaylist() exibe a playlist (musicas adicionadas) do usuario;
*/
void User::showPlaylist()
{
	if(playList.empty()){
		cout << "\n<<Playlist is empty!>>\n";
		return;
	}
	list<MusicTrack>::iterator pl;
	for(pl = playList.begin(); pl != playList.end(); pl++){
		(*pl).showMusicInformation(2);
	}
}

/*
	-Metodo idPlayListRemove() trata a entrada do usuario referente a exclusao de musicas;
	-Obriga o utilizador digitar um id de remocao dentro do intervalo de ids de musicas que este possui.
	-Retorna o id digitado em que se deseja remover da playlist.
*/
int User::idPlayListRemove()
{
	vector<int> ids;
	int idOption, len=0;
	list<MusicTrack>::iterator pl;
	for(pl = playList.begin(); pl != playList.end(); pl++)
		ids.push_back((*pl).getId());
	len = ids.size();
	std::sort (ids.begin(), ids.end(),Utilities::ascending);
	idOption = Utilities::readInt("\nType your choose: ",ids[0], ids[len-1]);
	return idOption;
}

/*
	-Metodo removeMusic() remove a musica da playlist, dado o id (caso seja possivel);
	-parametro id: identificador da musica que se deseja remover.
*/
void User::removeMusic(int id)
{
	list<MusicTrack>::iterator pl;
	for(pl = playList.begin(); pl != playList.end(); pl++){
		if(id == (*pl).getId()){
//			cout << "\n <<Music " << (*pl).getTitle() << " removed>>" << endl; // not applicable
			playList.erase(pl);
			return;
		}
	}
	cout << "\n\n<<This music is not in your playlist!>>";
}

/*
	-Metodo changeLike() menu de incremento de likes/dislikes;
	-parametro listOfMusicTrack: lista de musicas da RadioStation;
	-pergunta qual musica da RadioStation deseja incrementar likes/dislikes,
	 e depois pergunta se deseja dar likes ou dislikes.
	-Retona true caso consiga fazer esta operacao.
*/
bool User::changeLike(list<MusicTrack> &listOfMusicTrack)
{
	int idOption, optLike;
	idOption = showMusics(listOfMusicTrack);
	if(idOption==0){
		cout << "\n\n<<There are no Music in Radio Station>>" << endl;
		return false;
	}
	while(true){
		idOption = Utilities::readInt("\nWhich music do you want like/dislike?: ",1,idOption);
		list<MusicTrack>::iterator mus;
		for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++){
			if((*mus).getId() == idOption){
				optLike = Utilities::readInt("Like: [1] or Dislike: [2]? " ,1,2);
				switch(optLike){
					case 1:
						cout << "\n" << (*mus).getTitle() << " had his like incremented" << endl;
						(*mus).incrementLike();
						updatePlaylistUserFile(listOfMusicTrack);
					return true;
					case 2:
						cout << "\n" << (*mus).getTitle() << " had his dislike incremented" << endl;
						(*mus).incrementDislike();
						updatePlaylistUserFile(listOfMusicTrack);
					return true;
				}
			}
		}
		cout << "\nPlease, type a valid number!" << endl;
	}
}

/*
	-Metodo idInPlayList() verifica se determinada musica esta na playlist;
	-parametro idTarget: is da musica que se deseja verificar se esta na playlist;
	-Percorre a playlist e caso encontre a musica com idTarget, retorna true.
*/
bool User::idInPlayList(int idTarget)
{
	list<MusicTrack>::iterator pl;
	for(pl = playList.begin(); pl != playList.end(); pl++)
		if((*pl).getId() == idTarget)
			return true;
	return false;
}