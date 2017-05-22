/* RadioStation.cpp */
/* Classe que representa uma estacao de radio */
#include "RadioStation.h"

/* Construtores */
//--------------------------------------------------------------------------
RadioStation::RadioStation() { }

RadioStation::RadioStation(string _name){ name = _name; }

/* Outros Metodos */
//--------------------------------------------------------------------------

/*
	-Metodo displayAllTracks() exibe no ecra os campos de todas as musicas da RadioStation;
	-parametro optDisplay: indica a quantidade de campos que serao mostrados (ordem sequencial)
	-Ex: optDisplay=2 exibe apenas o id e o title
*/
void RadioStation::displayAllTracks(int optDisplay){
	if(listOfMusicTrack.empty()){
		cout << "\n\n<<There are no Music in Radio Station>>" << endl;
		return;
	}
	list<MusicTrack>::iterator mus;
	for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++){
		(*mus).showMusicInformation(optDisplay);
	}
}

/*
	-Metodo displayAllUsers() exibe no ecra os campos de todos os usuarios da RadioStation;
	-parametro optDisplay: indica a quantidade de campos que serao mostrados (ordem sequencial)
	-Ex: optDisplay=2 exibe apenas o id e o kindOfUser
*/
void RadioStation::displayAllUsers(int optDisplay){
	if(listOfUsers.empty()){
		cout << "\n\n<<There are no Users in Radio Station>>" << endl;
		return;
	}
	list<User>::iterator usr;
	for(usr = listOfUsers.begin(); usr != listOfUsers.end(); usr++){
		(*usr).showUserInformation(optDisplay);
	}
}

/*
	-Metodo showTopTen() exibe no ecra as 10 melhores musicas da RadioStation;
	 criterio de ordenacao: (like-dislike)
*/
void RadioStation::showTopTen(){
	if(topTenMusicTracks.empty()){
		cout << "\n\n<<There are no Music in Top Ten>>" << endl;
		return;
	}
	list<MusicTrack>::iterator mus;
	for(mus = topTenMusicTracks.begin(); mus != topTenMusicTracks.end(); mus++){
		(*mus).showMusicInformation(2);
	}
}

/*
	-Metodo interfaceUser() gerencia a entrada/registro de contas;
	 Entrar: necessario digitar o id da conta
	 Registrar: conta normal, basta digitar os dados da conta,
				conta administrador, necessario introduzir senha e preenchimento de dados.
*/
void RadioStation::interfaceUser()
{
	int choice, idIncrement, idUsr;
	loadRadioStationFiles();
	while(true){
		cout << "What you want to do?\n"   << endl;
		cout << "[1] Enter in a account"   << endl;
		cout << "[2] Register a new user"  << endl;
		cout << "[9] Exit\n" << endl;
		
		choice = Utilities::readInt("\nType your choose: ",1,9);
		switch(choice)
		{
			case 1:
				{
					if(listOfUsers.empty()){
						cout << "\n\n<<There are no registered users>>\n\n";
						break;
					}
					idIncrement = autoIncrementIdUSER();
					cout << "\n<<Entering an account>>\n" << endl;
					idUsr = Utilities::readInt("What is your id?: ",1,idIncrement-1);
					list<User>::iterator usr;
					User usrTemp(0);
					for(usr = listOfUsers.begin(); usr != listOfUsers.end(); usr++){
						if((*usr).getId() == idUsr){
							usrTemp = (*usr);
							userDomain(usrTemp);
							break;
						}
					}
					break;
				}
			case 2:
				cout << "\n<<Register of New User>>\n" << endl;
				idIncrement = autoIncrementIdUSER();
				{
					User u1(idIncrement);
					registerNewUser(u1);
					cout << "\n<<Registered! Your id is: " << idIncrement << " >>" << endl;
				}
			break;
			case 9:
				cout << "\nExit...\n" << endl;
				return;
			default:
				cout << "\nPlease, type a valid number!" << endl;
			break;
		}
		cout << endl;
	}
}

/* Load Files */
/*
	-Metodo loadRadioStationFiles() invoca o carregemento dos ficheiros ao programa;
*/
void RadioStation::loadRadioStationFiles()
{
	loadRadioMusicsFile();
	loadUsersFile();
	loadTopTenFile();
}

/*
	-Metodo loadRadioMusicsFile() carrega no programa as informacoes das musicas;
	-Nome do ficheiro: "radioStationMusics.csv";
	-As informacoes sao extraidas do ficheiro e adicionadas na lista de musicas desta classe.
*/
void RadioStation::loadRadioMusicsFile()
{
	ifstream fin;
	fin.open("radioStationMusics.csv");
	if(fin.fail()){
		fin.close();
//		cout << "\nFailure to open file 'radioStationMusics.csv' \n" << endl; /*error*/
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
			listOfMusicTrack.push_back(newMusic);
			commaPosition = 0;
			beginOfSubstring = 0;
			createNewMusic = true;
			fillFieldControl = 0;
		}
	}
	fin.close();
}

/*
	-Metodo loadUsersFile() carrega no programa as informacoes dos usuarios;
	-Nome do ficheiro: "users.csv";
	-As informacoes sao extraidas do ficheiro e adicionadas na lista de usuarios desta classe.
*/
void RadioStation::loadUsersFile()
{
	ifstream fin;
	fin.open("users.csv");
	if(fin.fail()){
		fin.close();
//		cout << "\nFailure to open file 'users.csv' \n" << endl; /*error*/
		return;
	}
	stringstream fieldWriter;
	string lineContent, Field;
	int commaPosition = 0;
	int beginOfSubstring = 0;
	bool createNewUser = true;
	int intField = 0;
	User newUser(intField);
	int fillFieldControl = 0;
	while(getline(fin, lineContent)){
		if(lineContent[0] != 'i'){
			while(commaPosition != -1){
				commaPosition = lineContent.find_first_of(',',commaPosition + 1);
				if(createNewUser){
					Field = lineContent.substr(beginOfSubstring, commaPosition - beginOfSubstring);
					intField = atoi(Field.c_str());
					createNewUser = false;
					newUser.setId(intField);
				}
				else{
					Field = lineContent.substr(beginOfSubstring, commaPosition - beginOfSubstring);
					switch(fillFieldControl){
						case 0:
							newUser.setKindOfUser(Field);
							break;
						case 1:
							newUser.setName(Field);
							break;
						case 2:
							intField = atoi(Field.c_str());
							newUser.setAge(intField);
							break;
						case 3:
							newUser.setGender(Field);
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
			listOfUsers.push_back(newUser);
			commaPosition = 0;
			beginOfSubstring = 0;
			createNewUser = true;
			fillFieldControl = 0;
		}
	}
	fin.close();
}

/*
	-Metodo loadTopTenFile() carrega no programa as informacoes das 10 melhores musicas;
	-Nome do ficheiro: "topTen.csv";
	-As informacoes sao extraidas do ficheiro e adicionadas na lista de melhores musicas desta classe.
*/
void RadioStation::loadTopTenFile()
{
	ifstream fin;
	fin.open("topTen.csv");
	if(fin.fail()){
		fin.close();
//		cout << "\nFailure to open file 'topTen.csv' \n" << endl; /*error*/
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
			topTenMusicTracks.push_back(newMusic);
			commaPosition = 0;
			beginOfSubstring = 0;
			createNewMusic = true;
			fillFieldControl = 0;
		}
	}
	fin.close();
}

/* Update Files */
/*
	-Metodo updateUsersFile() atualiza o ficheiro com as informacoes do usuario;
	-Nome do ficheiro: "users.csv";
	-As informacoes sao referentes aos usuarios contidas na lista de usuarios desta classe,
	 uma por linha, com campos separados por virgula.
	-parametro newUser: novo usuario que se deseja adicionar na RadioStation.
*/
void RadioStation::updateUsersFile(User &newUser)
{
	ifstream fin;
	ofstream fout;
	string s;
	stringstream userLine, aux;
	userLine << newUser.getId() << ',' << newUser.getkindOfUser() << ',' << newUser.getName() << ',' 
			 << newUser.getAge() << ',' << newUser.getGender();
	fin.open("users.csv");
	if(fin.fail()){
		fout.open("users.csv");
		fout << "id,kindOfUser,name,age,gender\n";
		fout << userLine.str();
	}
	else{
		while(getline(fin, s))
			aux << s << "\n";
		fout.open("users.csv");
		fout << aux.str();
		fout << userLine.str();
	}
	fin.close();
	fout.close();
}

/*
	-Metodo updateRadioMusicsFile() atualiza o ficheiro com as informacoes da lista de musicas;
	-Nome do ficheiro: "radioStationMusics.csv";
	-As informacoes sao referentes as musicas contidas na lista de musicas desta classe,
	 uma por linha, com campos separados por virgula.
*/
void RadioStation::updateRadioMusicsFile()
{
	ofstream fout;
	string s;
	stringstream musicLine;
	list<MusicTrack>::iterator mus;
	for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++){
		musicLine << (*mus).getId() << ',' << (*mus).getTitle() << ',' << (*mus).getArtist() << ',' << (*mus).getAuthor() << ',' << (*mus).getAlbum() 
		<< ',' << (*mus).getMusicGenre() << ',' << (*mus).getYear() << ',' << (*mus).getNumberOfLikes() << ',' << (*mus).getNumberOfDislikes() <<  '\n';
	}
	fout.open("radioStationMusics.csv");
	fout << "ID,Title,Artist,Author,Album,Genre,Year;Number of Likes,Number of Dislikes\n";
	fout << musicLine.str();
	fout.close();
}

/*
	-Metodo updateTopTenFile() atualiza o ficheiro com as informacoes da lista das 10 melhores musicas;
	-Nome do ficheiro: "topTen.csv";
	-As informacoes sao referentes as 10 melhores musicas contidas na lista de TOP musicas desta classe,
	 uma por linha, com campos separados por virgula.
*/
void RadioStation::updateTopTenFile()
{
	ofstream fout;
	string s;
	stringstream musicLine, aux;
	list<MusicTrack>::iterator mus;
	multimap<int,MusicTrack> mapQuality_Mus;
	int topMusic = topTen, i=0;

	topTenMusicTracks.clear();
	if(listOfMusicTrack.size()<topMusic)
		topMusic = listOfMusicTrack.size();

	for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++)
		mapQuality_Mus.insert(pair<int,MusicTrack>((*mus).getNumberOfDislikes()-(*mus).getNumberOfLikes(),(*mus)));

	for (multimap<int,MusicTrack>::iterator mm=mapQuality_Mus.begin(); mm!=mapQuality_Mus.end() && i<topMusic; ++mm, i++){
		topTenMusicTracks.push_back((*mm).second);
		musicLine << (*mm).second.getId() << ',' << (*mm).second.getTitle() << ',' << (*mm).second.getArtist() << ',' << (*mm).second.getAuthor() << ',' << (*mm).second.getAlbum() << ','
		<< (*mm).second.getMusicGenre() << ',' << (*mm).second.getYear() << ',' << (*mm).second.getNumberOfLikes() << ',' << (*mm).second.getNumberOfDislikes() << '\n';
	}

	fout.open("topTen.csv");
	fout << "ID,Title,Artist,Author,Album,Genre,Year;Number of Likes,Number of Dislikes\n";
	fout << musicLine.str();
	fout.close();
}

/* Register of New User */
/*
	-Metodo autoIncrementIdUSER() verifica qual id do ultimo usuario registrado;
	-Retorna o ultimo incrementado por 1.
*/
int RadioStation::autoIncrementIdUSER()
{
	ifstream fin; 
	string s, aux;
	int posComma=0;
	fin.open("users.csv");
	if(fin.fail())
		return 1;
	while(getline(fin, s));
	posComma = s.find(",",0);
	aux = s.substr(0,posComma);
	fin.close();
	return atoi(aux.c_str())+1;
}

/*
	-Metodo registerNewUser() coleta as informacoes dos campos necessarios para o
	 registro de um novo usuario (com tratamento das entradas).
	-parametro newUser: novo usuario que se deseja adicionar na RadioStation.
*/
void RadioStation::registerNewUser(User &newUser)
{
	int attempts=0;
	string password;
	string kindOfUser = Utilities::readString("\nKind of User [A]dministrator or [N]ormal: ", "a,n",2);
	if(kindOfUser == "a")
		while(attempts<attemptsFinal){
			cout << "\n<" << passwordADM << ">" << " password to create administrator: ";
			cin >> password;
			if(password == passwordADM)
				break;
			cout << "\n<<incorrect password>>\n";
			attempts++;
			if(attempts == attemptsFinal){
				cout << "\n<<access denied>>\n";
				return;
			}
		}
	newUser.setKindOfUser(kindOfUser);

	string name;
	cout  << "Name: ";
	fflush(stdin);
	getline(cin,name);
	newUser.setName(name);

	int age = Utilities::readInt("Age: ",0,150);
	newUser.setAge(age);

	string gender = Utilities::readString("Gender [M]ale or [F]emale: ", "m,f",2);
	newUser.setGender(gender);

	listOfUsers.push_back(newUser);
	updateUsersFile(newUser);
}

/* Entering an account */
/*
	-Metodo userDomain() gerencia as opcoes de utilizacao dos dois tipos de usuarios.
	-As funcionalidades da aplicacao sao invocadas deste metodo, que tem por objetivo
	 fazer interface com o utilizador a nivel de usuario dentro de uma conta.
*/
void RadioStation::userDomain(User &usr)
{
	int option, kindOfSearch;
	usr.loadPlaylist();
	while(true){
		if(usr.getkindOfUser() == "a"){
			cout << "\n<<Entering Administrator User Domain>>\n" << endl;
			cout << "Account of: " << usr.getName() << endl;
			cout << "\n[1] Manage Radio Station Playlist" << endl;
			cout << "[2] Display All Users" << endl;
			cout << "[3] Display All Music Tracks" << endl;
			cout << "[4] Generate Set of Musics Played in a Period" << endl;
			cout << "[5] Show Winner" << endl;
			cout << "[6] Reset Season Control" << endl;
			cout << "[9] Logout\n" << endl;
			option = Utilities::readInt("Type your choose: ",1,9);
			switch(option)
			{
				case 1:
					manageListOfTracks();
				break;
				case 2:
					displayAllUsers(userInformation);
				break;
				case 3:
					displayAllTracks(musicInformation);
				break;
				case 4:
					if(!listOfMusicTrack.empty()){
						randomSeason();
						showSeasonControl(false);
					}
					else
						cout << "\n\n<<There are no Music in Radio Station>>" << endl;
				break;
				case 5:
					if(!listOfMusicTrack.empty() && !seasonControl.empty())
						searchWinner();
					else
						cout << "\n\n<<There is not any music or music not yet been played>>" << endl;
				break;
				case 6:
					if(!seasonControl.empty()){
						cout << "\n<<Reset Season Control>>" << endl;
						seasonControl.clear();
					}
					else
						cout << "\n\n<<Season Control is empty now>>" << endl;
				break;
				case 9:
					cout << "\nLogout...\n" << endl;
					return;
				default:
					cout << "\nPlease, type a valid number!" << endl;
				break;
			}
		}
		else{
			cout << "\n<<Entering Normal User Domain>>\n" << endl;
			cout << "Account of: " << usr.getName() << endl;
			cout << "\n[1] Manage Playlist" << endl;
			cout << "[2] Display all Tracks in playList" << endl;
			cout << "[3] Like or Dislike any Music" << endl;
			cout << "[4] Consult Top Ten of the Radio Station" << endl;
			cout << "[5] Display Track by a given key" << endl;
			cout << "[9] Logout\n" << endl;
			option = Utilities::readInt("Type your choose: ",1,9);
			switch(option)
			{
				case 1:
					usr.managePlaysList(listOfMusicTrack);
				break;
				case 2:
					
					usr.updatePlaylistUserFile(listOfMusicTrack);
					usr.showPlaylist();
				break;
				case 3:
					if(usr.changeLike(listOfMusicTrack)){
						updateRadioMusicsFile();
						updateTopTenFile();
					}
				break;
				case 4:
					updateTopTenFile();
					showTopTen();
				break;
				case 5:
					cout << "\n[1] title / [2] year / [3] artist / [4] music genre / [5] author" << endl;
					kindOfSearch = Utilities::readInt("\nKind of Search: ",1,5);
					displayTracks(kindOfSearch);
				break;
				case 9:
					cout << "\nLogout...\n" << endl;
					return;
				default:
					cout << "\nPlease, type a valid number!" << endl;
				break;
			}
		}
		cout << endl;
	}
}

/*
	-Metodo manageListOfTracks() gerencia as opcoes de adicionar/remover 
	 musicas na lista de musicas da RadioStation;
	-Permanece no menu ate' que o usuario deseje sair.
*/
void RadioStation::manageListOfTracks()
{
	int choice, idIncrement, idRemove;
	cout << "\n<<Manage of List Tracks>>" << endl;
	while(true){
		cout << "\n[1] Add Music" << endl;
		cout << "[2] Remove Music" << endl;
		cout << "[9] Exit" << endl;
		choice = Utilities::readInt("\nType your choose: ",1,9);
		switch(choice)
		{
			case 1:
				cout << "\n<<Register of New Music>>\n" << endl;
				idIncrement = autoIncrementIdMUSIC();
				{
					MusicTrack m1(idIncrement);
					registerNewMusic(m1);
				}
			break;
			case 2:
				if(listOfMusicTrack.empty()){
					cout << "\n\n<<There are no Music in Radio Station>>";
					break;
				}
				displayAllTracks(2);
				cout << "\nWhich music do you want to remove[ID]?: " << endl;
				idRemove = idMusicRemove();
				removeMusicRadioStation(idRemove);
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
	-Metodo displayTracks() exibe no ecra as musicas encontradas dado uma chave de busca.
	-parametro kindOfReference: indica qual o tipo de busca.
	Ex: para kindOfReference=1 implica em busca de musicas por title.
*/
void RadioStation::displayTracks(int kindOfReference)
{
	if(listOfMusicTrack.empty()){
		cout << "\n\n<<There are no Music in Radio Station>>" << endl;
		return;
	}
	string key_str;
	int key_int;
	list<MusicTrack>::iterator mus;
	cout << "\nType the key of search: ";
	switch(kindOfReference){
	case 1:
		fflush(stdin);
		getline(cin,key_str);
		for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++)
			if((*mus).getTitle() == key_str)
				(*mus).showMusicInformation(musicInformation);
	break;
	case 2:
		key_int = Utilities::readInt("",-10000,10000);
		for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++)
			if((*mus).getYear() == key_int)
				(*mus).showMusicInformation(musicInformation);
	break;
	case 3:
		fflush(stdin);
		getline(cin,key_str);
		for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++)
			if((*mus).getArtist() == key_str)
				(*mus).showMusicInformation(musicInformation);
	break;
	case 4:
		fflush(stdin);
		getline(cin,key_str);
		for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++)
			if((*mus).getMusicGenre() == key_str)
				(*mus).showMusicInformation(musicInformation);
	break;
	case 5:
		fflush(stdin);
		getline(cin,key_str);
		for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++)
			if((*mus).getAuthor() == key_str)
				(*mus).showMusicInformation(musicInformation);
	break;
	}
	cout << "\n<What has been found is above>>" << endl;
}

/*
	-Metodo randomSeason() gera a quantidade de vezes que cada musica da estacao de radio foi tocada,
	 de forma aleatoria. Armazena estes dados em seasonControl.
*/
void RadioStation::randomSeason(){
	seasonControl.clear();
	cout << endl;
	list<MusicTrack>::iterator mus;
	for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++)
		seasonControl.insert(pair<int,MusicTrack>(Utilities::GetRandom(-maxMusicPlayedInPeriod,0),(*mus)));
}

/*
	-Metodo showSeasonControl() exibe no ecra a relacao de musica (id) por quantidade
	 de vezes que esta foi tocada em um periodo (referente ao campo seasonControl).
	-parametro completeInfo: se true exibe informacao complementar da musica.
*/
void  RadioStation::showSeasonControl(bool completeInfo)
{
	for (multimap<int,MusicTrack>::iterator it=seasonControl.begin(); it!=seasonControl.end(); ++it){
		if(completeInfo){
			cout << "Music: " << (*it).second.getTitle() << " of " << (*it).second.getArtist() << " was played:\t"
			<< -(*it).first << " times!" << endl;
		}
		else{
			cout << "id: " << (*it).second.getId() << " was played:\t" << -(*it).first << " times!" << endl;
	
		}
	}
}

/*
	-Metodo searchWinner() procura qual usuario possui mais hits (musicas mais tocadas)
	 e exibe este como vencedor. Caso nenhum usuario tenha algum hit em sua playlist,
	 um usuario aleatorio e' atribuido arbitrariamente como vencedor.
*/
void RadioStation::searchWinner()
{
	int i=0, userPoints=0, idWinner=0, topHits=topHitsMusics, maxId=0;
	vector <int> vecIdHit;
	multimap<int,int> mapHits_Id;
	multimap<int,int>::iterator itm;
	list<User>::iterator usr;

	if(listOfMusicTrack.size()<topHits)
		topHits = listOfMusicTrack.size();

	for (multimap<int,MusicTrack>::iterator itmm=seasonControl.begin(); itmm != seasonControl.end() && i<topHits; ++itmm, i++)
		vecIdHit.push_back((*itmm).second.getId());

	for(usr = listOfUsers.begin(); usr != listOfUsers.end(); usr++){
		(*usr).loadPlaylist();
		userPoints=topHits;
		if((*usr).getId()>maxId)
			maxId = (*usr).getId();
		for(int j=0 ; j<vecIdHit.size() ; j++){
			if((*usr).idInPlayList(vecIdHit.at(j))){
				userPoints--;
			}
		}
		mapHits_Id.insert(pair<int,int>(userPoints,(*usr).getId()));
	}
	itm  = mapHits_Id.begin();
	idWinner = (*itm).second;
	if((*itm).first == topHits){
		cout << "\n<<There are no User with any Top Hit>>\n";
		cout << "  A winner will be generated random\n";
		idWinner = Utilities::GetRandom(1,maxId+1);
	}
	for(usr = listOfUsers.begin(); usr != listOfUsers.end(); usr++)
		if(idWinner == (*usr).getId())
			cout << "\nWinner: " << (*usr).getName() << " with id: " << (*usr).getId() << "\n";
}

/*
	-Metodo autoIncrementIdMUSIC() verifica qual id da ultima musica adicionada;
	-Retorna o ultimo incrementado por 1.
*/
int RadioStation::autoIncrementIdMUSIC()
{
	int maxId=0;
	list<MusicTrack>::iterator mus;
	for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++)
		if((*mus).getId() > maxId)
			maxId = (*mus).getId();
	return maxId+1;
}

/*
	-Metodo registerNewMusic() coleta as informacoes dos campos necessarios para o
	 registro de uma nova musica (com tratamento das entradas).
	-parametro newMusic: nova musica que se deseja adicionar a lista de musicas.
*/
void RadioStation::registerNewMusic(MusicTrack &newMusic)
{
	string title;
	cout  << "Title: ";
	fflush(stdin);
	getline(cin,title);
	newMusic.setTitle(title);

	string artist;
	cout  << "Artist: ";
	fflush(stdin);
	getline(cin,artist);
	newMusic.setArtist(artist);

	string author;
	cout  << "Author: ";
	fflush(stdin);
	getline(cin,author);
	newMusic.setAuthor(author);

	string album;
	cout  << "Album: ";
	fflush(stdin);
	getline(cin,album);
	newMusic.setAlbum(album);

	string genre;
	cout  << "Genre: ";
	fflush(stdin);
	getline(cin,genre);
	newMusic.setMusicGenre(genre);

	int year = Utilities::readInt("Year: ",-10000,10000);
	newMusic.setYear(year);

	newMusic.setNumberOfLikes(0);
	newMusic.setNumberOfDislikes(0);

	listOfMusicTrack.push_back(newMusic);
	updateRadioMusicsFile();
	if(!topTenMusicTracks.empty())
		updateTopTenFile();
}

/*
	-Metodo idMusicRemove() trata a entrada do usuario referente a exclusao de musicas;
	-Obriga o utilizador digitar um id de remocao dentro do intervalo de ids de musicas que este possui.
	-Retorna o id digitado em que se deseja remover da lista de musicas.
*/
int RadioStation::idMusicRemove(){
	vector<int> ids;
	int idOption, len=0;
	list<MusicTrack>::iterator mus;
	for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++)
		ids.push_back((*mus).getId());
	len = ids.size();
	std::sort (ids.begin(), ids.end(),Utilities::ascending);
	idOption = Utilities::readInt("\nType your choose: ",ids[0], ids[len-1]);
	return idOption;
}

/*
	-Metodo removeMusicRadioStation() remove a musica da RadioStation, dado o id (caso seja possivel);
	-parametro id: identificador da musica que se deseja remover.
*/
void RadioStation::removeMusicRadioStation(int id)
{
	list<MusicTrack>::iterator mus;
	for(mus = listOfMusicTrack.begin(); mus != listOfMusicTrack.end(); mus++){
		if(id == (*mus).getId()){
			cout << "\n <<Music " << (*mus).getTitle() << " removed>>" << endl;
			listOfMusicTrack.erase(mus);
			updateRadioMusicsFile();
			if(!topTenMusicTracks.empty())
				updateTopTenFile();
			removeMusicUser(id);
			return;
		}
	}
	cout << "\n\n<<This music is not in your playlist!>>";
}

/*
	-Metodo removeMusicUser() remove a musica dos usuarios que a possuem dado o id;
	-parametro id: identificador da musica que se deseja remover.
*/
void RadioStation::removeMusicUser(int id)
{
	list<User>::iterator usr;
	for(usr = listOfUsers.begin(); usr != listOfUsers.end(); usr++){
		(*usr).loadPlaylist();
		if((*usr).idInPlayList(id)){
			(*usr).removeMusic(id);
			(*usr).updatePlaylistUserFile(listOfMusicTrack);
		}
	}
}