/* RadioStation.h */
/* Classe que representa uma estacao de radio */

#ifndef RADIOSTATION_H_
#define RADIOSTATION_H_

#include "User.h"
#include "MusicTrack.h"
#include "Utilities.h"
#include <list>
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
using namespace std;
const int musicInformation = 9; //quantidade de campos de uma musica
const int userInformation = 5;  //quantidade de campos de um usuario
const int topTen = 10;			//quantidade de musicas consideradas na classificacao de melhores (like-dislike)
const int maxMusicPlayedInPeriod = 10; //indica o maximo possivel que uma musica pode ser tocada em um periodo
const int topHitsMusics= 3;	//quantidade de musicas consideradas como Hits (as tres mais tocadas em um periodo)
const int attemptsFinal= 3; //tentativas ao tentar digitar a senha na criacao de uma conta do tipo administrador
const string passwordADM = "feup"; //senha necessaria para criar uma conta do tipo administrador

class RadioStation {
private:
	/* Atributos */
	string name;
	list<User> listOfUsers;					//usuarios registrados
	list<MusicTrack> listOfMusicTrack;		//musicas da estacao de radio
	list<MusicTrack> topTenMusicTracks;		//melhores musicas ordenadas por (like-dislike)
	multimap<int,MusicTrack> seasonControl; //relacao entre <vezes que foi tocada/periodo, musica>
	/* Metodos Privados */
	void loadRadioMusicsFile();
	void loadUsersFile();
	void loadTopTenFile();
	int autoIncrementIdUSER();
	int autoIncrementIdMUSIC();
	void updateUsersFile(User &newUser);

public:
	/* Construtores */
	RadioStation();
	RadioStation(string _name);
	/* Outros Metodos */
	void displayAllTracks(int optDisplay);
	void displayAllUsers(int optDisplay);
	void interfaceUser();
	void loadRadioStationFiles();
	/* Administratot User*/
	void manageListOfTracks();
	void randomSeason();
	void showSeasonControl(bool completeInfo);
	void searchWinner();
	void removeMusicRadioStation(int idRemove);
	void removeMusicUser(int id);
	int idMusicRemove();
	/* Normal User*/
	void registerNewUser(User &newUser);
	void registerNewMusic(MusicTrack &newMusic);
	void userDomain(User &usr);
	void updateRadioMusicsFile();
	void updateTopTenFile();
	void showTopTen();
	void displayTracks(int kindOfReference);
};

#endif
