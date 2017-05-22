/* User.h */
/* Classe que representa um Usuario */

#ifndef USER_H_
#define USER_H_

#include "MusicTrack.h"
#include "Utilities.h"
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class User {
private:
	int id;		//identificador do usuario (aplicacao garante que este e' unico)
	string kindOfUser;			//administrador ou normal
	string name;
	int age;
	string gender;
	list <MusicTrack> playList; //lista de musicas do usuario

public:
	/* Construtores */
	User();
	User(int _id);
	/* Metodos get e set */
	void setId(int _id);
	void setKindOfUser(string _kindOfUser);
	void setName(string _name);
	void setAge(int _age);
	void setGender(string _gender);
	int getId();
	string getkindOfUser();
	string getName();
	int getAge();
	string getGender();
	list<MusicTrack> getPlayList();

	/* Outros Metodos */
	void showUserInformation(int optDisplay);
	void loadPlaylist();
	void managePlaysList(list<MusicTrack> &listOfMusicTrack);
	void updatePlaylistUserFile(list<MusicTrack> &listOfMusicTrack);
	/* Add Music */
	int showMusics(list<MusicTrack> &listOfMusicTrack);
	void addMusic(list<MusicTrack> &listOfMusicTrack, int idOption);
	/* Remove Music */
	void showPlaylist();
	int idPlayListRemove();
	void removeMusic(int id);
	/* Give Like/Dislike */
	bool changeLike(list<MusicTrack> &listOfMusicTrack);
	bool idInPlayList(int idTarget);
};

#endif
