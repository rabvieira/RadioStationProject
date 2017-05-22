/* MusicTrack.h */
/* Classe que representa uma musica */

#ifndef MUSICTRACK_H_
#define MUSICTRACK_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class MusicTrack {
private:
	int id;  	 //identificador da musica (aplicacao garante que este e' unico)
	string title;
	string artist;
	string author;
	string album;
	string musicGenre;
	int year;
	int numberOfLikes;    //quantidade de likes creditados a musica por qualquer usuario
	int numberOfDislikes; //quantidade de dislikes creditados a musica por qualquer usuario

public:
	/* Construtores */
	MusicTrack();
	MusicTrack(int _id);
	/* Metodos get e set */
	void setId(int _id);
	void setTitle(string _title);
	void setArtist(string _artist);
	void setAuthor(string _author);
	void setAlbum(string _album);
	void setMusicGenre(string _musicGenre);
	void setYear(int _year);
	void setNumberOfLikes(int _NOL);
	void setNumberOfDislikes(int _NOD);
	int getId();
	string getTitle();
	string getArtist();
	string getAuthor();
	string getAlbum();
	string getMusicGenre();
	int getYear();
	int getNumberOfLikes();
	int getNumberOfDislikes();
	/* Outros Metodos */
	void showMusicInformation(int optDisplay); //mostra os atributos da musica no ecra
	void incrementLike();	  //incrimenta o campo numberOfLikes
	void incrementDislike();  //incrimenta o campo numberOfDislikes
};

#endif
