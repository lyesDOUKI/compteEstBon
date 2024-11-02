#include<iostream>
#include<list>
#include<stack>
#include<string>
#include<fstream>
#include<limits>
using namespace std;

void valeur_absolue(int& x)     //cette procédure me permettra de calculer la valeur absolue
								// de la difference entre la cible et l'approximation (ou le calcul obtenu)
{
	int n;
	if (x < 0)
	{
		x = x * (-1);
	}
}
void affichage_pile(stack<string>ma_pile)            //cette procedure affichera ma pile bestsol
{
	while (!ma_pile.empty())  //on verifie si la pille n'est pas vide
	{
		cout << ma_pile.top() << endl; //on affiche le premier element
		ma_pile.pop(); // on dépile
	}
}
list<int> sauvegarde_liste_initial(list<int>ma_liste) //cette fonction sauvegardera ma liste initiale obtenu aprés la lecture du fichier
{
	list<int>liste; //variable list à retourner en fin de fonction
	list<int>::iterator p; //un itérateur pour parcourir ma liste
	for (p = ma_liste.begin(); p != ma_liste.end(); p++)  //on parcour la liste du debut en initialisant l'itérateur p au debut 
														//on s'arrete quand on est arrive en fin de liste
	{
		liste.push_back(*p);   //push_back rajoute la valeur pointer par p en queue de liste
	}
	return liste;
}
void affichage_liste(list<int>ma_liste)      //cette procedure affichera ma liste initial
{
	list<int>::iterator p; //un itérateur pour parcourir ma liste
	for (p = ma_liste.begin(); p != ma_liste.end(); p++) //on parcour la liste du debut en initialisant l'itérateur p au debut 
														//on s'arrete quand on est arrive en fin de liste
	{
		cout << *p << " ";
	}
	cout << endl;
}
list<int> calcul(list<int>& liste, list<int>::iterator i, list<int>::iterator j, int op) //op=1--> +  op=2--> -  op=3--> *  op=4--> /  
{
	int val, a, b, n;  //a = la valeur pointé par i    b = la valeur pointé par j       val = le resultat du calcul entre a et b
	list<int>nouv_liste;  // variable list à retourner à la fin de la fonction
	a = (*i);  // a recoit la valeur pointé par i
	b = (*j);  // b recoit la valeur pointé par j
	if (op == 1) // 1 correspond à l'addition
	{
		val = a + b;
	}
	if (op == 2) // 2 correspond à la soustraction
	{
		if (a > b)
		{
			val = a - b;
			if (val == 0)          // si la valeur calculé est egale à 0, on la prend pas en compte
			{
				val = -1;
			}
		}
		else   // si b>a 		cela nous evitra d'avoir un resultat negatif
		{
			val = b - a;
			if (val == 0)           // si la valeur calculé est egale à 0, on la prend pas en compte
			{
				val = -1;
			}
		}
	}
	if (op == 3)        // 3 correspond à la multiplication
	{
		val = a * b;
	}
	if (op == 4)    // 4 correspond à la division 
	{
		if (a > b)   // on teste si a est plus grand b
		{
			n = a % b;  // on calcule le reste de la divion a sur b
			if (n != 0) // si le reste n'es pas egale à 0 on ne prend pas en compte l'operation
			{
				val = -1;
			}
			if (n == 0)  // si le reste egale à 0
			{
				val = a / b;  // on devise a sur b
			}


		}
		if (b >= a)        // on teste si b est plus grand a
		{
			n = b % a;     // on calcule le reste de la divion b sur a
			if (n != 0)     // si le reste n'es pas egale à 0 on ne prend pas en compte l'operation
			{
				val = -1;
			}
			if (n == 0)     // si le reste egale à 0
			{
				val = b / a;       // on devise b sur a
			}
		}
	}
	if (val != -1)   //condition pour savoir si le calcul est pris en compte
	{
		nouv_liste.push_back(val);   // on insere la valeur en queue de la nouvelle liste

		list<int>::iterator p;   // un itérateur pour parcourir ma liste
		p = liste.begin();   // on initialise l'itérateur en debut de la liste initial pris en paramètre 
		while (p != liste.end())    // tant que on a pas fini de parcourir la liste
		{
			if (p == i or p == j)   // si l'iterateur p est egale aux itérateur pris en paramètre
			{
				++p;  // on avance dans la liste
					// cette condition nous permettra de remplir la nouvelle liste sans les valeur calculé precedemment
			}
			else
			{
				nouv_liste.push_back(*p); // on insere les autres elements de la liste initial dans la nouvelle liste
				++p; //on avance dans la liste
			}
		}
	}
	return nouv_liste;


}

bool enumeration(list<int>& liste, int cible, int& approx, stack<string>& sol, stack<string>& bestsol)  //cette fonction s'occupera d'enumérer tout les calcul recursivement
{

	int element1 = liste.front();  // on sauvegarde le premier element de la liste en paramètre de la fonction
	list<int>temp;   // une liste temporaire elle correspond à la liste obtenu aprés un calcul


	int operation, k, taille, z, diff1, diff2; // operation ==> 1,2,3,4 (+,-,*,/)   
										 // k nous aidera à parcourir la liste du premier element de la liste jusqu'à l'avant dernier element de la liste
										// taille correspond à la taille de la liste pris en paramètre de la fonction
										// z nous aidera à parcourir la liste de l'element k+1 jusqu'au dernier element de la liste
										// diff1 ==> la cible - le calcul fait 
										// diff2 ==> la cible - l'approximation


	list<int>::iterator it1, it2;    // deux itérateur pour parcourir la liste est accéder au valeur
	taille = liste.size();  // on stocke la taille de la liste 

	if (taille == 1 and approx != cible)    //si la liste ne contient que un element et que ce dernier n'est pas la cible 
	{
		return false;
	}
	if (approx == cible)     //si l'approximation est égale à la cible 
	{
		return true;
	}
	else    // l'approximation est differente de la cible 
	{
		if (taille >= 2)  //si on a au moin deux element, c'est le minimum pour faire des calculs
		{
			for (k = 0; k <= taille - 2; k = k + 1)  // k de 0 jusqu'a la taille -2 avec k qui s'incremente de +1
										// taille-2 correspondra à l'avant dernier element de la liste
			{
				it1 = liste.begin();   // on initialise l'itérateur en debut de la liste
				advance(it1, k);    //cette procedure permet d'avancer l'iterateur it1 de k position 
									//(k=0 ==> it1 en debut de liste, k==taille-2 ==> it1 avant dernier element de la liste)

				for (z = k + 1; z <= taille - 1; z = z + 1)			// z de k+1 jusqu'a la taille -1 avec z qui s'incremente de +1
														// taille-1 correspondra à l'avant dernier element de la liste
				{
					it2 = liste.begin();      // on initialise l'itérateur en debut de la liste
					advance(it2, z);          //cette procedure permet d'avancer l'iterateur it1 de k position 
											//(z=1 ==> it2 deuxieme element de la liste, z==taille-1 ==> it2 dernier element de la liste) 

					for (operation = 1; operation <= 4; operation++)   // une boucle pour faire toutes les operations
					{
						temp = calcul(liste, it1, it2, operation);   // on forme notre nouvelle liste apres le calculs sur les pointeur it1 et it2
						diff1 = cible - temp.front();  // diff1 ==> la cible - le calcul fait 
						diff2 = cible - approx;   // diff2 ==> la cible - l'approximation
						valeur_absolue(diff1);    //on fait la valeur absolue de diff1 et diff2
						valeur_absolue(diff2);    // pour eviter de travailler avec des valeurs negatives
						if (diff1 < diff2)        //cette condition nous permettra de savoir si la valeur calculé est plus proche de la cible
						{
							approx = temp.front();    // approx deviens l'element calculé
						}
						string a, b, c, oper;         // ces variable là me permettront de convertir les entier en string pour constuire mes pile de string
						oper = "";    //j'initialise une chaine vide
						a = to_string(*it1);    // je converti la valeur du pointeur it1 en string
						b = to_string(*it2);    // je converti la valeur du pointeur it2 en string
						c = to_string(temp.front()); // je converti la valeur calculé en string

						if (operation == 1)      //si on fait une addition 
						{
							if (*it1 > *it2)    //cette condition me permettra d'afficher la valeur la plus grande à gauche
							{
								oper += a;
								oper += "+";             // je concaténe mes variable string entre elle pour former l'operation 
								oper += b;
								oper += "=";
								oper += c;
							}
							else         //cette condition me permettra d'afficher la valeur la plus grande à gauche
							{
								oper += b;
								oper += "+";			// je concaténe mes variable string entre elle pour former l'operation 
								oper += a;
								oper += "=";
								oper += c;
							}

						}
						if (operation == 2)			//si on fait une soustraction 
						{
							if (*it1 > *it2)			//cette condition me permettra d'afficher la valeur la plus grande à gauche
							{
								oper += a;
								oper += "-";			// je concaténe mes variable string entre elle pour former l'operation 
								oper += b;
								oper += "=";
								oper += c;
							}
							else  					//cette condition me permettra d'afficher la valeur la plus grande à gauche
							{
								oper += b;
								oper += "-";			// je concaténe mes variable string entre elle pour former l'operation 
								oper += a;
								oper += "=";
								oper += c;
							}


						}
						if (operation == 3)			//si on fait une multiplication
						{
							if (*it1 > *it2)			//cette condition me permettra d'afficher la valeur la plus grande à gauche
							{
								oper += a;
								oper += "*";			// je concaténe mes variable string entre elle pour former l'operation
								oper += b;
								oper += "=";
								oper += c;
							}
							else					//cette condition me permettra d'afficher la valeur la plus grande à gauche
							{
								oper += b;
								oper += "*";			// je concaténe mes variable string entre elle pour former l'operation
								oper += a;
								oper += "=";
								oper += c;
							}

						}
						if (operation == 4)		//si on fait une division
						{
							if (*it1 > *it2)			//cette condition me permettra d'afficher la valeur la plus grande à gauche
							{
								oper += a;
								oper += "/";			// je concaténe mes variable string entre elle pour former l'operation
								oper += b;
								oper += "=";
								oper += c;
							}
							else				//cette condition me permettra d'afficher la valeur la plus grande à gauche
							{
								oper += b;
								oper += "/";			// je concaténe mes variable string entre elle pour former l'operation
								oper += a;
								oper += "=";
								oper += c;
							}

						}
						sol.push(oper);   //cette methode nous permet d'empiler un element

						if (enumeration(temp, cible, approx, sol, bestsol))   // si mon appel recursif est vrai (si la cible egale à approx)
						{
							bestsol.push(oper);       //j'empile le calcul fait pour atteindre la cible
							return true;      // ce return true nous permet de sortir de la fonction recursif avec la valeur true
											// tout les appels recursifs antérieur à celui ou en atteindra la cible seront true
						}

					}


				}
			}

		}
	}
	return false;

}






int main()
{
	cout << "============================================Le Compte Est Bon !================================================" << endl;
	cout << endl;
	cout << "Le but de cette epreuve est d'obtenir un nombre, dit cible, tirer au hasard entre [101, 999]" << endl;
	cout << "a partir d'operations elementaires(additon +, soustraction -, multiplication x, division /) sur des entiers naturels" << endl;
	cout << "en partant de 6 nombres tirer aussi au hasard(sans remise) dans l'ensemble : {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,25,50,75,100}" << endl;

	int quitter = 0;
	while (quitter == 0)
	{
		int ma_cible, var, u, h;
		cout << endl;
		cout << "donnez une cible entre 101 et 999 : " << endl;
		cin >> ma_cible;
		while (cin.fail() or (ma_cible < 101) or (ma_cible > 999))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "donnez une cible entre 101 et 999 : " << endl;
			cin >> ma_cible;

		}
		list<int>l, liste_initial;
		cout << "tirez 6 nombre a partir de cet ensemble : " << endl;
		cout << "{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 25, 50, 75, 100}" << endl;
		cout << "ecrivez le nombre et tapez entrer : " << endl;
		list<int>ensemble = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 25, 50, 75, 100 };
		list<int>::iterator v;

		h = 0;
		while (h < 6)
		{
			bool trouve = false;
			cin >> var;
			v = ensemble.begin();
			while ((trouve == false) and (v != ensemble.end()))
			{
				if (var == *v)
				{
					trouve = true;
				}
				else
				{
					v++;
				}
			}
			if (trouve == true)
			{
				liste_initial.push_back(var);
				ensemble.erase(v);
			}
			else
			{
				cout << "erreur, retapez de nouveau : " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			h = liste_initial.size();
		}

		list<int>::iterator p1, p2, p;    // p1,p2 seront les arguments de la fonction calculs
									//p nous aidera à trouvé le maximum de la liste   
		stack<string>s1, s2;      			//s1==>sol   s2 ==>bestsol
		bool verifie;         			//variable qui verifiera le retour de la fonction ennumeration
		int cib, max, approxim; 								 //cib ==> la cible à atteindre   max ==> le maximum de la liste  approxim ==> la valeur la plus proche dans le cas ou le compte n'est pas bon
											  //on utilise la fonction lecture pour avoir la cible
		cout << "la cible est : " << ma_cible << endl;    // on affiche la cible 
		cout << "ma liste initial : " << endl;
		affichage_liste(liste_initial);  // on affiche la liste initial
		cout << "==================================================================" << endl;
		int t;
		t = liste_initial.size();   // t ==> la taille de la liste (cette fonction retourne la taille de la liste)
		liste_initial.sort();   //cette fonction va trier la liste dans l'ordre croissant
		p = liste_initial.begin();  // on initialise p au debut 
		advance(p, t - 1);   // on place p sur le dernier element de la liste
		max = *p; 			// vu que la liste est trié dans l'ordre croissant, le dernier element serra le plus grand de la liste
		verifie = enumeration(liste_initial, ma_cible, max, s1, s2);  // on appel la fonction enumeration avec la liste_intial
														// la cible en deuxieme argument
														//le max en 3 eme argument car logiquement au debut, le plus grand de la liste c'est le plus proche de la cible
														//les piles s1 et s2 

		if (verifie == true) 		//si on trouve la cible   
		{
			cout << "le compte est bon ! " << endl;
			cout << "les calculs faits : " << endl;
			affichage_pile(s2);        //on affiche les calculs faits pour atteindre la cible
		}
		if (verifie == false)    // si on a pas trouvé la cible 
						//c'est ici que on va traité l'approximation 
		{
			approxim = max;   //la variable approxim recevera max (vu que max est transmit par valeur, il sortira à la fin de la fonction avec une autre valeur)
						// et si verifie egale false, la valeur de max serra la valeur la plus proche de la cible 
						// approxim recevera cette valeur est on refait un autre appel avec la cible = approxim(on est sur de trouvé la cible)

			liste_initial.sort();  //on trie la liste initial 
			p = liste_initial.begin(); //on initialise p au debut de la liste
			advance(p, t - 1);   // on place p sur le dernier element de la liste qui est le plus grand
			max = *p;    //on stocke le maximum de la liste dans max 
			cout << "non, on ne peut malheureusement pas atteindre la cible :( " << endl;
			cout << "la meilleur approximation : " << approxim << endl;
			cout << "les calculs faits : " << endl;
			if (enumeration(liste_initial, approxim, max, s1, s2))        //on refait l'appel recursif avec cette fois la cible = approxim 
			{
				affichage_pile(s2);   //on affiche les caluls fait pour atteindre l'approximation
			}
		}
		cout << "voulez vous rejouer ? tapez o si oui ou une autre touche pour quitter " << endl;
		char q;
		cin >> q;
		if (toupper(q) != 'O')
		{
			quitter++;
		}
	}
	return 1;

}