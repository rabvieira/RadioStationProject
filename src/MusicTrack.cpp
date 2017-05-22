/* MusicTrack.cpp */
/* Classe que representa uma musica */
#include "MusicTrack.h"

/* Construtores */
//--------------------------------------------------------------------------
MusicTrack::MusicTrack() { }

MusicTrack::MusicTrack(int _id){ id = _id; }

/* Metodos set */
//--------------------------------------------------------------------------
void MusicTrack::setId(int _id){ id = _id; }

void MusicTrack::setTitle(string _title){ title = _title; }

void MusicTrack::setArtist(string _artist){ artist = _artist; }

void MusicTrack::setAuthor(string _author){ author = _author; }

void MusicTrack::setAlbum(string _album){ album = _album; }

void MusicTrack::setMusicGenre(string _musicGenre){ musicGenre = _musicGenre; }

void MusicTrack::setYear(int _year){ year = _year; }

void MusicTrack::setNumberOfLikes(int NOL){ numberOfLikes = NOL; }

void MusicTrack::setNumberOfDislikes(int NOD){ numberOfDislikes = NOD; }

/* Metodos get */
//--------------------------------------------------------------------------
int MusicTrack::getId(){ return id; }

string MusicTrack::getTitle(){ return title; }

string MusicTrack::getArtist(){ return artist; }

string MusicTrack::getAuthor(){ return author; }

string MusicTrack::getAlbum(){ return album; }

string MusicTrack::getMusicGenre(){ return musicGenre; }

int MusicTrack::getYear(){ return year; }

int MusicTrack::getNumberOfLikes(){ return numberOfLikes; }

int MusicTrack::getNumberOfDislikes(){ return numberOfDislikes; }

/* Outros Metodos */
//--------------------------------------------------------------------------
/*
	-Metodo showMusicInformation() exibe no ecra os campos da musica;
	-parametro optDisplay: indica a quantidade de campos que serao mostrados (ordem sequencial)
	-Ex: optDisplay=2 exibe apenas o id e o title
*/
void MusicTrack::showMusicInformation(int optDisplay)
{
	cout << endl;
	for(int i=0 ; i<optDisplay ; i++){
		switch(i){
			case 0:
				cout << "\nid:\t"     << id;
			break;
			case 1:
				cout << "\nTitle:\t"  << title;
			break;
			case 2:
				cout << "\nArtist:\t" << artist;
			break;
			case 3:
				cout << "\nAuthor:\t" << author;
			break;
			case 4:
				cout << "\nAlbum:\t"  << album;
			break;
			case 5:
				cout << "\nGenre:\t"  << musicGenre;
			break;
			case 6:
				cout << "\nYear:\t"   << year;
			break;
			case 7:
				cout << "\nLikes:    " << numberOfLikes;
			break;
			case 8:
				cout << "\nDislikes: " << numberOfDislikes;
			break;
			default:
				return;
			break;
		}
	}
	cout << endl;
}

/*
	Metodo incrementLike() incrimenta o campo numberOfLikes da musica
*/
void MusicTrack::incrementLike()
{
	numberOfLikes+=1;
}

/*
	Metodo incrementDislike() incrimenta o campo numberOfDislikes da musica
*/
void MusicTrack::incrementDislike()
{
	numberOfDislikes+=1;
}