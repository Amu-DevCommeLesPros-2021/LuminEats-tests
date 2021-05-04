#include "test_harness/test_harness.h"

#include "db/db.h"
#include "db/tables.h"
#include "logger/logger.h"
#include "lumineats/lumineats.h"
#include "vector/vector.h"

#include <sys/stat.h>
#include <unistd.h>

#if defined(__linux__)
    #define  _POSIX_C_SOURCE 200809L
#endif
#include <stdio.h>

// Valeurs pour le harnais de test spécifiques à ce programme.
int const tests_total = 301;
int const test_column_width = 60;

int main()
{
    system("rm -rf build/test-db && mkdir -p build/test-db && cp -a test/db/. build/test-db");

    // Tests de lecture et d'écriture de la table 'restaurants'.
    {
        FILE *test_db_restaurants = fopen("build/test-db/restaurants.csv", "r");
        vector restaurants = lecture_table_restaurants(test_db_restaurants);
        fclose(test_db_restaurants);

        TEST(size(restaurants) == 3);

        restaurant *r = (restaurant*)value(begin(&restaurants));
        TEST(r->index == 1);
        TEST(strcmp(r->nom, "Chez Michel") == 0);
        TEST(strcmp(r->code_postal, "13001") == 0);
        TEST(strcmp(r->telephone, "04 13 13 13 13") == 0);
        TEST(strcmp(r->type, "provencal") == 0);
        TEST(r->menu[0] == 1);
        TEST(r->menu[1] == 4);
        TEST(r->menu[2] == 5);
        TEST(r->menu[3] == 0);
        TEST(r->menu[TAILLE_MENU - 1] == 0);
        TEST(r->solde == 50);

        r = (restaurant*)value(at(&restaurants, 2));
        TEST(r->index == 3);
        TEST(strcmp(r->nom, "Joe's International House of Pancakes") == 0);
        TEST(strcmp(r->code_postal, "13010") == 0);
        TEST(strcmp(r->telephone, "04 22 33 44 55") == 0);
        TEST(strcmp(r->type, "americain") == 0);
        TEST(r->menu[0] == 6);
        TEST(r->menu[1] == 7);
        TEST(r->menu[2] == 0);
        TEST(r->menu[TAILLE_MENU - 1] == 0);
        TEST(r->solde == 44);

        FILE *test_db_restaurants_copie = fopen("build/test-db/restaurants-copie.csv", "w");
        ecriture_table_restaurants(test_db_restaurants_copie, &restaurants);
        fclose(test_db_restaurants_copie);
        TEST_FILE("build/test-db/restaurants.csv", "build/test-db/restaurants-copie.csv");

        destroy(&restaurants);
    }

    // Tests de lecture et d'écriture de la table 'items'.
    {
        FILE *test_db_items = fopen("build/test-db/items.csv", "r");
        vector items = lecture_table_items(test_db_items);
        fclose(test_db_items);

        TEST(size(items) == 7);

        item *i = (item*)value(begin(&items));
        TEST(i->index == 1);
        TEST(strcmp(i->nom, "bouillabaisse") == 0);
        TEST(strcmp(i->ingredients[0], "poissons de roche") == 0);
        TEST(strcmp(i->ingredients[1], "pommes de terre") == 0);
        TEST(strcmp(i->ingredients[2], "") == 0);
        TEST(i->prix == 25);

        i = (item*)value(at(&items, 6));
        TEST(i->index == 7);
        TEST(strcmp(i->nom, "petit-dej du champion") == 0);
        TEST(strcmp(i->ingredients[0], "oeufs") == 0);
        TEST(strcmp(i->ingredients[1], "toast") == 0);
        TEST(strcmp(i->ingredients[2], "bacon") == 0);
        TEST(strcmp(i->ingredients[3], "pomme de terre") == 0);
        TEST(strcmp(i->ingredients[4], "") == 0);
        TEST(i->prix == 12);

        FILE *test_db_items_copie = fopen("build/test-db/items-copie.csv", "w");
        ecriture_table_items(test_db_items_copie, &items);
        fclose(test_db_items_copie);
        TEST_FILE("build/test-db/items.csv", "build/test-db/items-copie.csv");

        destroy(&items);
    }

    // Tests de lecture et d'écriture de la table 'livreurs'.
    {
        FILE *test_db_livreurs = fopen("build/test-db/livreurs.csv", "r");
        vector livreurs = lecture_table_livreurs(test_db_livreurs);
        fclose(test_db_livreurs);

        TEST(size(livreurs) == 3);

        livreur *l = (livreur*)value(begin(&livreurs));
        TEST(l->index == 1);
        TEST(strcmp(l->nom, "Francois Pignon") == 0);
        TEST(strcmp(l->telephone, "06 00 00 00 00") == 0);
        TEST(strcmp(l->deplacements[0], "13001") == 0);
        TEST(strcmp(l->deplacements[1], "13002") == 0);
        TEST(strcmp(l->deplacements[2], "13003") == 0);
        TEST(strcmp(l->deplacements[3], "") == 0);
        TEST(l->restaurant == 1);
        TEST(l->solde == 20);

        l = (livreur*)value(at(&livreurs, 2));
        TEST(l->index == 3);
        TEST(strcmp(l->nom, "Mickey Mouse") == 0);
        TEST(strcmp(l->telephone, "06 11 22 33 44") == 0);
        TEST(strcmp(l->deplacements[0], "13008") == 0);
        TEST(strcmp(l->deplacements[1], "13009") == 0);
        TEST(strcmp(l->deplacements[2], "13010") == 0);
        TEST(strcmp(l->deplacements[3], "13011") == 0);
        TEST(strcmp(l->deplacements[4], "") == 0);
        TEST(l->restaurant == 0);
        TEST(l->solde == 0);

        FILE *test_db_livreurs_copie = fopen("build/test-db/livreurs-copie.csv", "w");
        ecriture_table_livreurs(test_db_livreurs_copie, &livreurs);
        fclose(test_db_livreurs_copie);
        TEST_FILE("build/test-db/livreurs.csv", "build/test-db/livreurs-copie.csv");

        destroy(&livreurs);
    }

    // Tests de lecture et d'écriture de la table 'clients'.
    {
        FILE *test_db_clients = fopen("build/test-db/clients.csv", "r");
        vector clients = lecture_table_clients(test_db_clients);
        fclose(test_db_clients);

        TEST(size(clients) == 4);

        client *c = (client*)value(begin(&clients));
        TEST(c->index == 1);
        TEST(strcmp(c->nom, "Francoise Perrin") == 0);
        TEST(strcmp(c->code_postal, "13005") == 0);
        TEST(strcmp(c->telephone, "04 10 20 30 40") == 0);
        TEST(c->solde == 0);

        c = (client*)value(at(&clients, 2));
        TEST(c->index == 3);
        TEST(strcmp(c->nom, "Quentin Tarantino") == 0);
        TEST(strcmp(c->code_postal, "13008") == 0);
        TEST(strcmp(c->telephone, "06 99 88 77 66") == 0);
        TEST(c->solde == 15);

        FILE *test_db_clients_copie = fopen("build/test-db/clients-copie.csv", "w");
        ecriture_table_clients(test_db_clients_copie, &clients);
        fclose(test_db_clients_copie);
        TEST_FILE("build/test-db/clients.csv", "build/test-db/clients-copie.csv");

        destroy(&clients);
    }

    // Tests des fonctions de convénience de lecture et d'écriture de la DB.
    {
        ouverture_db("build/test-db");

        TEST(size(table_restaurants) == 3);
        TEST(strcmp(((restaurant*)value(begin(&table_restaurants)))->nom, "Chez Michel") == 0);

        TEST(size(table_items) == 7);
        TEST(strcmp(((item*)value(begin(&table_items)))->nom, "bouillabaisse") == 0);

        TEST(size(table_livreurs) == 3);
        TEST(strcmp(((livreur*)value(begin(&table_livreurs)))->nom, "Francois Pignon") == 0);

        TEST(size(table_clients) == 4);
        TEST(strcmp(((client*)value(begin(&table_clients)))->nom, "Francoise Perrin") == 0);

        mkdir("build/test-db/ecriture", 0755);
    
        fermeture_db("build/test-db/ecriture");
        TEST_FILE("build/test-db/restaurants.csv", "build/test-db/ecriture/restaurants.csv");
        TEST_FILE("build/test-db/items.csv", "build/test-db/ecriture/items.csv");
        TEST_FILE("build/test-db/livreurs.csv", "build/test-db/ecriture/livreurs.csv");
        TEST_FILE("build/test-db/clients.csv", "build/test-db/ecriture/clients.csv");
    }

    // Tests pour le système de journal.
    {
        char const* chemin_journal = "test-log.txt";

        lopen(chemin_journal);
        llog("Ceci est un %s, %d", "test", 123);
        lclose();

        // Confirm the file contains the message.
        FILE *log = fopen(chemin_journal, "r");
        char *buffer = NULL;
        size_t buffer_size;
        getline(&buffer, &buffer_size, log);

        TEST(strstr(buffer, "Ceci est un test, 123") != NULL);

        free(buffer);
        fclose(log);
        remove(chemin_journal);
    }

    // Tests d'existence de comptes.
    {
        ouverture_db("build/test-db");

        // Parmi les comptes Restaurateurs.
        TEST(le_compte_existe("Chez Michel") == true);
        TEST(le_compte_existe("04 22 33 44 55") == true);
        
        // Parmi les comptes Livreurs.
        TEST(le_compte_existe("Donald Duck") == true);
        TEST(le_compte_existe("06 00 00 00 00") == true);

        // Parmi les comptes Clients.
        TEST(le_compte_existe("Quentin Tarantino") == true);
        TEST(le_compte_existe("04 10 20 30 40") == true);

        // Tests négatifs.
        TEST(le_compte_existe("") == false);
        TEST(le_compte_existe("La Rotonde") == false);
        TEST(le_compte_existe("00 00 00 00 00") == false);

        fermeture_db("build/test-db");
    }

    // Tests d recherche de comptes.
    {
        ouverture_db("build/test-db");

        // Parmi les comptes Restaurateurs.
        TEST(strcmp(le_cherche_restaurant("Chez Michel")->nom, "Chez Michel") == 0);
        TEST(strcmp(le_cherche_restaurant("04 22 33 44 55")->telephone, "04 22 33 44 55") == 0);
        
        // Parmi les comptes Livreurs.
        TEST(strcmp(le_cherche_livreur("Donald Duck")->nom, "Donald Duck") == 0);
        TEST(strcmp(le_cherche_livreur("06 00 00 00 00")->telephone, "06 00 00 00 00") == 0);

        // Parmi les comptes Clients.
        TEST(strcmp(le_cherche_client("Quentin Tarantino")->nom, "Quentin Tarantino") == 0);
        TEST(strcmp(le_cherche_client("04 10 20 30 40")->telephone, "04 10 20 30 40") == 0);

        // Tests négatifs.
        TEST(le_cherche_restaurant("") == NULL);
        TEST(le_cherche_restaurant("La Rotonde") == NULL);
        TEST(le_cherche_restaurant("00 00 00 00 00") == NULL);

        fermeture_db("build/test-db");
    }

    // Tests de creation de comptes.
    mkdir("build/test-db/creation-compte", 0755);
    {
        // Création d'un compte Restaurateur.
        ouverture_db("build/test-db/creation-compte");
        char nom_restaurant[] = "Snack-Bar Chez Raymond";
        cle_t ixr1 = le_creer_compte_restaurateur(nom_restaurant, "13001", "04 00 00 00 00", "fast food");
        restaurant const* const r = le_cherche_restaurant_i(ixr1);
        
        TEST(le_compte_existe(nom_restaurant) == true);
        TEST(strcmp(r->nom, nom_restaurant) == 0);

        fermeture_db("build/test-db/creation-compte");

        // Vérification intrusive du fichier 'restaurants.csv'.
        FILE *restaurants = fopen("build/test-db/creation-compte/restaurants.csv", "r");
        char *buffer = NULL;
        size_t buffer_size;
        getline(&buffer, &buffer_size, restaurants);
        getline(&buffer, &buffer_size, restaurants);

        TEST(strcmp(buffer, "1,Snack-Bar Chez Raymond,13001,04 00 00 00 00,fast food,,0\n") == 0);

        fclose(restaurants);

        // Création d'un compte Livreur.
        ouverture_db("build/test-db/creation-compte");
        char nom_livreur[] = "Bob Binette";
        cle_t ixl = le_creer_compte_livreur(nom_livreur, "04 99 99 99 99", "13001", 0);
        livreur const* const l = le_cherche_livreur_i(ixl);

        TEST(le_compte_existe(nom_livreur) == true);
        TEST(strcmp(l->nom, nom_livreur) == 0);

        fermeture_db("build/test-db/creation-compte");

        // Vérification intrusive du fichier 'livreurs.csv'.
        FILE *livreurs = fopen("build/test-db/creation-compte/livreurs.csv", "r");
        getline(&buffer, &buffer_size, livreurs);
        getline(&buffer, &buffer_size, livreurs);

        TEST(strcmp(buffer, "1,Bob Binette,04 99 99 99 99,13001,0,0\n") == 0);

        fclose(livreurs);

        // Création d'un compte Client.
        ouverture_db("build/test-db/creation-compte");
        char nom_client[] = "Paul Pitron";
        cle_t ixc = le_creer_compte_client(nom_client, "13001", "06 66 66 66 66");
        client const* const c = le_cherche_client_i(ixc);

        TEST(le_compte_existe(nom_client) == true);
        TEST(strcmp(c->nom, nom_client) == 0);

        fermeture_db("build/test-db/creation-compte");

        // Vérification intrusive du fichier 'clients.csv'.
        FILE *clients = fopen("build/test-db/creation-compte/clients.csv", "r");
        getline(&buffer, &buffer_size, clients);
        getline(&buffer, &buffer_size, clients);

        TEST(strcmp(buffer, "1,Paul Pitron,13001,06 66 66 66 66,0\n") == 0);

        free(buffer);
        fclose(clients);

        // Tests négatifs. Les noms ou téléphones existent déjà dans la BdD.
        ouverture_db("build/test-db/creation-compte");
        ixr1 = le_creer_compte_restaurateur("Snack-Bar Chez Raymond", "13001", "04 11 11 11 11", "fast food");
        TEST(ixr1 == 0);

        ixl = le_creer_compte_livreur("Bobby Binette", "04 99 99 99 99", "", 0);
        TEST(ixl == 0);

        ixc = le_creer_compte_client("Paul Pitron", "13001", "06 66 66 66 66");
        TEST(ixc == 0);
        
        fermeture_db("build/test-db/creation-compte");
    }

    // Tests de suppression de compte.
    mkdir("build/test-db/suppression-compte", 0755);
    {
        // Suppression d'un compte Restaurateur.
        ouverture_db("build/test-db/suppression-compte");
        char nom_restaurant[] = "Snack-Bar Chez Raymond";
        le_creer_compte_restaurateur(nom_restaurant, "13001", "04 00 00 00 00", "fast food");
        le_supprimer_compte(nom_restaurant);

        TEST(le_compte_existe(nom_restaurant) == false);

        fermeture_db("build/test-db/suppression-compte");

        // Vérification intrusive du fichier 'restaurants.csv'.
        FILE *restaurants = fopen("build/test-db/suppression-compte/restaurants.csv", "r");
        char *buffer = NULL;
        size_t buffer_size;
        getline(&buffer, &buffer_size, restaurants);
        TEST(getline(&buffer, &buffer_size, restaurants) == -1);

        fclose(restaurants);

        // Suppression d'un compte Livreur.
        ouverture_db("build/test-db/suppression-compte");
        char nom_livreur[] = "Bob Binette";
        le_creer_compte_livreur(nom_livreur, "04 99 99 99 99", "", 0);
        le_supprimer_compte(nom_livreur);

        TEST(le_compte_existe(nom_livreur) == false);
        
        fermeture_db("build/test-db/suppression-compte");

        // Vérification intrusive du fichier 'livreurs.csv'.
        FILE *livreurs = fopen("build/test-db/suppression-compte/livreurs.csv", "r");
        getline(&buffer, &buffer_size, livreurs);
        TEST(getline(&buffer, &buffer_size, livreurs) == -1);

        fclose(livreurs);

        // Suppression d'un compte Client.
        ouverture_db("build/test-db/suppression-compte");
        char nom_client[] = "Paul Pitron";
        le_creer_compte_client(nom_client, "13001", "06 66 66 66 66");
        le_supprimer_compte(nom_client);

        TEST(le_compte_existe(nom_client) == false);

        fermeture_db("build/test-db/suppression-compte");

        // Vérification intrusive du fichier 'clients.csv'.
        FILE *clients = fopen("build/test-db/suppression-compte/clients.csv", "r");
        getline(&buffer, &buffer_size, clients);
        TEST(getline(&buffer, &buffer_size, clients) == -1);

        free(buffer);
        fclose(clients);


        // Tests négatifs. Supprimer un compte qui n'existe pas ne doit pas affecter les comptes existants.
        ouverture_db("build/test-db/suppression-compte");
        le_creer_compte_restaurateur(nom_restaurant, "13001", "04 11 11 11 11", "fast food");
        le_creer_compte_livreur(nom_livreur, "04 99 99 99 99", "", 0);
        le_creer_compte_client(nom_client, "13001", "06 66 66 66 66");

        le_supprimer_compte("Inexistant");

        TEST(le_compte_existe(nom_restaurant) == true);
        TEST(le_compte_existe(nom_livreur) == true);
        TEST(le_compte_existe(nom_client) == true);

        fermeture_db("build/test-db/suppression-compte");
    }

    // Tests de modification de profils.
    mkdir("build/test-db/modification-profil", 0755);
    {
        ouverture_db("build/test-db/modification-profil");

        // Modification d'un compte livreur.
        char nom_livreur[] = "Louis Lamotte";
        cle_t ixl = le_creer_compte_livreur(nom_livreur, "06 11 11 11 11", "" , 0);
        livreur const* l = le_cherche_livreur_i(ixl);

        // On peut modifier le profil d'un livreur avec un nouveau téléphone.
        TEST(le_modifier_profil_livreur(l->index, "", "06 22 22 22 22", 0) == true);
        l = le_cherche_livreur(nom_livreur);
        TEST(strcmp(l->telephone, "06 22 22 22 22") == 0);

        // On peut modifier le profil d'un livreur avec des codes postaux de déplacement.
        TEST(le_modifier_profil_livreur(l->index, "13001", "06 22 22 22 22", 0) == true);
        l = le_cherche_livreur(nom_livreur);
        TEST(strcmp(l->deplacements[0], "13001") == 0);
        TEST(strcmp(l->deplacements[1], "") == 0);
        
        TEST(le_modifier_profil_livreur(l->index, "13001;13002;13003", "06 22 22 22 22", 0) == true);
        l = le_cherche_livreur(nom_livreur);
        TEST(strcmp(l->deplacements[0], "13001") == 0);
        TEST(strcmp(l->deplacements[1], "13002") == 0);
        TEST(strcmp(l->deplacements[2], "13003") == 0);
        TEST(strcmp(l->deplacements[3], "") == 0);

        // On peut modifier le profile d'un livreur avec l'index d'un restaurateur.
        cle_t const ixr1 = le_creer_compte_restaurateur("Cafe de la Gare", "13001", "000", "cafe");
        restaurant const* r = le_cherche_restaurant_i(ixr1);

        TEST(le_modifier_profil_livreur(l->index, "13001;13002;13003", "06 22 22 22 22", r->index) == true);
        l = le_cherche_livreur_i(ixl);
        TEST(l->restaurant == r->index);

        // On ne peut pas modifier un compte livreur pour lui donner un téléphone existant.
        ixl = le_creer_compte_livreur("Lucas Lamotte", "06 33 33 33 33", "", 0);
        l = le_cherche_livreur_i(ixl);
        TEST(le_modifier_profil_livreur(l->index, "13002", "06 22 22 22 22", 0) == false);

        // On ne peut pas modifier un compte ivreur pour lui donner un index de restaurant inexistant.
        TEST(le_modifier_profil_livreur(l->index, "13002", "08 88 88 88 88", 99) == false);

        // Livreur inexistant.
        TEST(le_modifier_profil_livreur(99, "", "09 99 99 99 99", 0) == false);


        // Modification d'un compte client.
        char nom_client[] = "Paul Pitron";
        cle_t ixc = le_creer_compte_client(nom_client, "13001", "06 66 66 66 66");
        client const* c = le_cherche_client_i(ixc);

        // On peut modifier le profil d'un client avec un nouveau code postal .
        TEST(le_modifier_profil_client(ixc, "13002", "06 66 66 66 66"));
        c = le_cherche_client_i(ixc);
        TEST(strcmp(c->code_postal, "13002") == 0);

        // On peut modifier le profil d'un client avec un nouveau téléphone.
        TEST(le_modifier_profil_client(c->index, "13002", "05 55 55 55 55"));
        c = le_cherche_client_i(ixc);
        TEST(strcmp(c->telephone, "05 55 55 55 55") == 0);

        // On peut modifier le profil d'un client avec de nouveaux code postal et téléphone.
        TEST(le_modifier_profil_client(c->index, "13002", "07 77 77 77 77"));
        c = le_cherche_client_i(ixc);
        TEST(strcmp(c->code_postal, "13002") == 0);
        TEST(strcmp(c->telephone, "07 77 77 77 77") == 0);

        // On  ne peut pas modifier un compte client pour lui donner un téléphone existant.
        ixc = le_creer_compte_client("Raoul Pitron", "13001", "08 88 88 88 88");
        c = le_cherche_client_i(ixc);

        TEST(le_modifier_profil_client(c->index, "13002", "07 77 77 77 77") == false);

        // Client inexistant.
        TEST(le_modifier_profil_client(99, "13002", "09 99 99 99 99") == false);

        fermeture_db("build/test-db/modification-profil");
    }

    // Tests d'ajout de crédits pour un client.
    mkdir("build/test-db/modification-solde", 0755);
    {
        ouverture_db("build/test-db/modification-solde");

        char nom_client[] = "Paul Pitron";
        cle_t const ixc = le_creer_compte_client(nom_client, "13001", "06 66 66 66 66");
        client const* c = le_cherche_client_i(ixc);

        TEST(c->solde == 0);

        le_crediter_solde_client(c->index, 1);
        c = le_cherche_client_i(ixc);
        TEST(c->solde == 1);

        le_crediter_solde_client(c->index, 10);
        c = le_cherche_client_i(ixc);
        TEST(c->solde == 1 + 10);

        fermeture_db("build/test-db/modification-solde");
    }

    // Tests des filtres pour restaurants.
    {
        ouverture_db("build/test-db");

        // Tests de filtre par type. 
        vector rs = le_liste_restaurants();
        vector restaurants = make_vector(sizeof(cle_t), 0);
        assign(&restaurants, begin(&rs), end(&rs));
        le_filtrer_restaurants_type(&restaurants, "provencal");
        
        TEST(size(restaurants) == 1);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 0)))->nom, "Chez Michel") == 0);

        // Re-filtrer avec le même type ne devrait rien changer.
        le_filtrer_restaurants_type(&restaurants, "provencal");
        
        TEST(size(restaurants) == 1);

        // Re-filtrer avec un type différent devrait tout enlever. 
        le_filtrer_restaurants_type(&restaurants, "italien");
        
        TEST(size(restaurants) == 0);

        // Tests par possibilité de livraison.

        // Test de qui peut livrer dans le 13001.
        assign(&restaurants, begin(&rs), end(&rs));
        le_filtrer_restaurants_livraison(&restaurants, "13001");

        TEST(size(restaurants) == 2);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 0)))->nom, "Chez Michel") == 0);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 1)))->nom, "Le Veg") == 0);

        // Test de qui peut livrer dans le 13002.
        assign(&restaurants, begin(&rs), end(&rs));
        le_filtrer_restaurants_livraison(&restaurants, "13002");
        
        TEST(size(restaurants) == 1);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 0)))->nom, "Chez Michel") == 0);

        // Test de qui peut livrer dans le 13005.
        assign(&restaurants, begin(&rs), end(&rs));
        le_filtrer_restaurants_livraison(&restaurants, "13005");
        
        TEST(size(restaurants) == 2);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 0)))->nom, "Chez Michel") == 0);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 1)))->nom, "Le Veg") == 0);

        // Test de qui peut livrer dans le 13009.
        assign(&restaurants, begin(&rs), end(&rs));
        le_filtrer_restaurants_livraison(&restaurants, "13009");
        
        TEST(size(restaurants) == 3);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 0)))->nom, "Chez Michel") == 0);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 1)))->nom, "Le Veg") == 0);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 2)))->nom, "Joe's International House of Pancakes") == 0);

        // Test de qui peut livrer dans le 13010.
        assign(&restaurants, begin(&rs), end(&rs));
        le_filtrer_restaurants_livraison(&restaurants, "13010");
        
        TEST(size(restaurants) == 1);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 0)))->nom, "Joe's International House of Pancakes") == 0);


        // Test négatifs.
        assign(&restaurants, begin(&rs), end(&rs));
        le_filtrer_restaurants_livraison(&restaurants, "13012");
        
        TEST(size(restaurants) == 0);


        // Test de deux filtres.
        assign(&restaurants, begin(&rs), end(&rs));
        le_filtrer_restaurants_livraison(&restaurants, "13009");
        le_filtrer_restaurants_type(&restaurants, "americain");
        
        TEST(size(restaurants) == 1);
        TEST(strcmp(le_cherche_restaurant_i(*(cle_t*)value(at(&restaurants, 0)))->nom, "Joe's International House of Pancakes") == 0);


        assign(&restaurants, begin(&rs), end(&rs));
        le_filtrer_restaurants_livraison(&restaurants, "13001");
        le_filtrer_restaurants_type(&restaurants, "americain");
        
        TEST(size(restaurants) == 0);

        destroy(&restaurants);
        destroy(&rs);

        fermeture_db("build/test-db/ecriture");
    }

    // Tests de modification des items.
    mkdir("build/test-db/items", 0755);
    {
        ouverture_db("build/test-db/items");

        vector items = le_liste_items();
        TEST(size(items) == 0);
        destroy(&items);

        cle_t const ixi1 = le_creer_item("croissant", "beurre;farine;oeuf;levure", 1);
        TEST(ixi1 != 0);
        item const* const i1 = le_cherche_item_i(ixi1);
        TEST(strcmp(i1->nom, "croissant") == 0);
        TEST(strcmp(i1->ingredients[0], "beurre") == 0);
        TEST(strcmp(i1->ingredients[1], "farine") == 0);
        TEST(strcmp(i1->ingredients[2], "oeuf") == 0);
        TEST(strcmp(i1->ingredients[3], "levure") == 0);
        TEST(strcmp(i1->ingredients[4], "") == 0);
        TEST(i1->prix == 1);

        items = le_liste_items();
        TEST(size(items) == 1);
        destroy(&items);

        // Il est possible de créer plus d'un item avec le même nom.
        cle_t const ixi2 = le_creer_item("croissant", "margarine;farine;oeuf;levure", 1);
        TEST(ixi2 != 0);
        item const* const i2 = le_cherche_item_i(ixi2);
        TEST(strcmp(i2->nom, "croissant") == 0);
        TEST(strcmp(i2->ingredients[0], "margarine") == 0);

        items = le_liste_items();
        TEST(size(items) == 2);
        destroy(&items);

        // Ajoute des items au menu d'un restaurant.
        cle_t const ixr1 = le_creer_compte_restaurateur("Café de la gare", "13001", "04 01 01 01 01", "boulangerie");
        le_ajouter_item_menu(ixi1, ixr1);

        restaurant const* r1 = le_cherche_restaurant_i(ixr1);
        TEST(r1->menu[0] == ixi1);
        TEST(r1->menu[1] == 0);
        TEST(strcmp(r1->menu_s, "1") == 0);

        le_ajouter_item_menu(ixi2, ixr1);
        TEST(r1->menu[0] == ixi1);
        TEST(r1->menu[1] == ixi2);
        TEST(r1->menu[2] == 0);
        TEST(strcmp(r1->menu_s, "1;2") == 0);

        // Ajoute les même items au menu d'un deuxième restaurant.
        cle_t const ixr2 = le_creer_compte_restaurateur("Café en face du Café de la gare", "13001", "04 02 02 02 02", "boulangerie");
        le_ajouter_item_menu(ixi1, ixr2);
        le_ajouter_item_menu(ixi2, ixr2);
        
        restaurant const* const r2 = le_cherche_restaurant_i(ixi2);

        TEST(r2->menu[0] == ixi1);
        TEST(r2->menu[1] == ixi2);
        TEST(r2->menu[2] == 0);
        TEST(strcmp(r2->menu_s, "1;2") == 0);


        // Si on enlève cet item d'un menu, l'item existe encore puisqu'il fait toujours parti d'au moins un menu.
        le_enlever_item_menu(ixi1, ixr1);
        r1 = le_cherche_restaurant_i(ixr1);

        TEST(r1->menu[0] == ixi2);
        TEST(r1->menu[1] == 0);
        TEST(strcmp(r1->menu_s, "2") == 0);

        items = le_liste_items();
        TEST(size(items) == 2);
        destroy(&items);

        // Si on enlève cet item de tous les menus, l'item n'apparait plus dans la BdD.
        le_enlever_item_menu(ixi1, ixr2);

        items = le_liste_items();
        TEST(size(items) == 1);
        destroy(&items);

        fermeture_db("build/test-db/items");
    }

    // Tests des filtres pour items de menu.
    {
        ouverture_db("build/test-db");

        // Tests de filtre par type. 
        vector is = le_liste_items();
        vector items = make_vector(sizeof(cle_t), 0);
        assign(&items, begin(&is), end(&is));


        // Filtrer par type 'provencal' devrait nous donner tous les items de 'Chez Michel'.
        le_filtrer_items_type(&items, "provencal");

        TEST(size(items) == 3);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "bouillabaisse") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 1)))->nom, "ratatouille") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 2)))->nom, "salade nicoise") == 0);

        // Re-filtrer avec le même type ne devrait rien changer.
        le_filtrer_items_type(&items, "provencal");

        TEST(size(items) == 3);

        // Re-filtrer avec le type 'vegetarien' devrait nous laisser avec la ratatouille qui est aussi offerte par 'Le Veg'. 
        le_filtrer_items_type(&items, "vegetarien");

        TEST(size(items) == 1);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "ratatouille") == 0);

        // Re-re-filtrer avec 'americain' ne devrait plus rien laisser de disponible.
        le_filtrer_items_type(&items, "americain");

        TEST(size(items) == 0);


        // Filtrer par restaurant.
        assign(&items, begin(&is), end(&is));

        le_filtrer_items_restaurant(&items, "Chez Michel");

        TEST(size(items) == 3);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "bouillabaisse") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 1)))->nom, "ratatouille") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 2)))->nom, "salade nicoise") == 0);

        // Re-filtrer avec le même restaurant ne devrait rien changer.
        le_filtrer_items_restaurant(&items, "Chez Michel");

        TEST(size(items) == 3);

        // En pratique, j'imagine que l'application ne va pas offrir de «re-filtrer» par restaurant.
        // Ce serait d'une utilité un peu incongrue. 

        // En théorie, on s'attendrait à ce que re-filtrer avec un autre restaurant ne 
        // laisse rien mais ce n'est pas ce qui va se passer ici car la fonction ne peut pas
        // savoir qu'on a déjà filtrer une première fois. Re-filtrer nous donne donc comme 
        // résultat une intersection des items offert par plusieurs restaurants.

        le_filtrer_items_restaurant(&items, "Le Veg");

        TEST(size(items) == 1);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "ratatouille") == 0);


        // Filtrer par prix.
        assign(&items, begin(&is), end(&is));

        // Devrait garder tous les items car aucun ne dépasse 100€.
        le_filtrer_items_prix(&items, 100);

        TEST(size(items) == 7);

        // Re-filter avec 20€ comme plafond devrait enelver la bouillabaisse.
        le_filtrer_items_prix(&items, 20);

        TEST(size(items) == 6);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "taco") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 5)))->nom, "petit-dej du champion") == 0);

        // Re-re-filter avec 9€ comme plafond ne devrait plus laisser que les trois items les moins chers.
        le_filtrer_items_prix(&items, 9);

        TEST(size(items) == 3);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "taco") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 1)))->nom, "houmous") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 2)))->nom, "pancakes aux myrtilles") == 0);

        // Re-re-re-filtrer avec 4€ comme plafond ne devrait plus laisser que le taco.
        le_filtrer_items_prix(&items, 4);

        TEST(size(items) == 1);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "taco") == 0);

        // Filtrer la liste originale avec 4€ comme plafond ne devrait laisser que le taco.
        assign(&items, begin(&is), end(&is));
        le_filtrer_items_prix(&items, 4);

        TEST(size(items) == 1);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "taco") == 0);


        // Re-filtrer avec 0€ ne devrait plus rien laisser.
        le_filtrer_items_prix(&items, 0);

        TEST(size(items) == 0);


        // Tests par possibilité de livraison.

        // Test des items qui peuvent être livrés dans le 13001.
        assign(&items, begin(&is), end(&is));

        le_filtrer_items_livraison(&items, "13001");

        TEST(size(items) == 5);
        // L'ordre n'est évidement pas strictement important mais il sera dans l'ordre de la table des items.
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "bouillabaisse") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 4)))->nom, "salade nicoise") == 0);

        // Test des items qui peuvent être livrés dans le 13002.
        assign(&items, begin(&is), end(&is));

        le_filtrer_items_livraison(&items, "13002");
        
        TEST(size(items) == 3);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "bouillabaisse") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 2)))->nom, "salade nicoise") == 0);

        // Test des items qui peuvent être livrés dans le 13005.
        assign(&items, begin(&is), end(&is));
        le_filtrer_items_livraison(&items, "13005");

        TEST(size(items) == 5);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "bouillabaisse") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 4)))->nom, "salade nicoise") == 0);

        // Test des items qui peuvent être livrés dans le 13009.
        assign(&items, begin(&is), end(&is));
        le_filtrer_items_livraison(&items, "13009");

        TEST(size(items) == 7);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "bouillabaisse") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 6)))->nom, "petit-dej du champion") == 0);

        // Test des items qui peuvent être livrés dans le 13010.
        assign(&items, begin(&is), end(&is));
        le_filtrer_items_livraison(&items, "13010");

        TEST(size(items) == 2);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "pancakes aux myrtilles") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 1)))->nom, "petit-dej du champion") == 0);

        // Test des items qui peuvent être livrés dans le 13012.
        assign(&items, begin(&is), end(&is));
        le_filtrer_items_livraison(&items, "13012");

        TEST(size(items) == 0);


        // Tests de plusieurs filtres.

        // Quel items coûtant 9€ ou mins peuvent être livré dans le 13009 ?
        assign(&items, begin(&is), end(&is));
        le_filtrer_items_livraison(&items, "13005");
        le_filtrer_items_prix(&items, 9);

        TEST(size(items) == 2);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "taco") == 0);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 1)))->nom, "houmous") == 0);

        // Quels items sont de cuisine 'américaine' et peuvent coûte moins de 10€ ?
        assign(&items, begin(&is), end(&is));
        le_filtrer_items_prix(&items, 9);
        le_filtrer_items_type(&items, "americain");

        TEST(size(items) == 1);
        TEST(strcmp(le_cherche_item_i(*(cle_t*)value(at(&items, 0)))->nom, "pancakes aux myrtilles") == 0);

        destroy(&items);
        destroy(&is);

        fermeture_db("build/test-db");
    }

    // Tests de commandes.
    mkdir("build/test-db/commande", 0755);
    {
        ouverture_db("build/test-db");

        vector items = make_vector(sizeof(cle_t), 0);
        vector non_livrables = make_vector(sizeof(cle_t), 0);
        vector depassent_solde = make_vector(sizeof(cle_t), 0);

        cle_t ixi;
        // Une commande simple et valide.
        ixi = 6; push_back(&items, &ixi);
        ixi = 7; push_back(&items, &ixi);

        TEST(le_valider_commande(2, &items, &non_livrables, &depassent_solde) == true);
        TEST(size(items) == 2);
        TEST(size(non_livrables) == 0);
        TEST(size(depassent_solde) == 0);

        // Une commande qui ne contient que des items qui ne peuvent être livrés.
        clear(&items);
        ixi = 1; push_back(&items, &ixi);
        ixi = 2; push_back(&items, &ixi);
        ixi = 3; push_back(&items, &ixi);
        ixi = 4; push_back(&items, &ixi);
        ixi = 5; push_back(&items, &ixi);

        TEST(le_valider_commande(2, &items, &non_livrables, &depassent_solde) == false);
        TEST(size(items) == 0);
        TEST(size(non_livrables) == 5);
        TEST(*(cle_t*)value(at(&non_livrables, 0)) == 1);
        TEST(*(cle_t*)value(at(&non_livrables, 4)) == 5);
        TEST(size(depassent_solde) == 0);

        // Une commande qui va dépasser le solde disponible.
        clear(&items);
        clear(&non_livrables);
        clear(&depassent_solde);
        ixi = 6; push_back(&items, &ixi);
        ixi = 7; push_back(&items, &ixi);
        ixi = 6; push_back(&items, &ixi);
        ixi = 7; push_back(&items, &ixi);
        ixi = 6; push_back(&items, &ixi);
        ixi = 7; push_back(&items, &ixi);   // À partir de cet item, le total dépasse le solde disponible.
        ixi = 6; push_back(&items, &ixi);
        ixi = 7; push_back(&items, &ixi);

        TEST(le_valider_commande(2, &items, &non_livrables, &depassent_solde) == false);
        TEST(size(items) == 5);
        TEST(size(non_livrables) == 0);
        TEST(size(depassent_solde) == 3);
        TEST(*(cle_t*)value(at(&depassent_solde, 0)) == 7);
        TEST(*(cle_t*)value(at(&depassent_solde, 1)) == 6);
        TEST(*(cle_t*)value(at(&depassent_solde, 2)) == 7);

        // Une commande qui contient des items dont seulement certains peuvent être livrés et
        // parmi ceux-ci, des items qui vont dépasser le solde disponible.
        clear(&items);
        clear(&non_livrables);
        clear(&depassent_solde);
        ixi = 1; push_back(&items, &ixi);
        ixi = 2; push_back(&items, &ixi);
        ixi = 3; push_back(&items, &ixi);
        ixi = 4; push_back(&items, &ixi);
        ixi = 5; push_back(&items, &ixi);
        ixi = 6; push_back(&items, &ixi);
        ixi = 7; push_back(&items, &ixi);

        TEST(le_valider_commande(3, &items, &non_livrables, &depassent_solde) == false);
        TEST(size(items) == 1);
        TEST(*(cle_t*)value(at(&items, 0)) == 6);

        TEST(size(non_livrables) == 5);
        TEST(*(cle_t*)value(at(&non_livrables, 0)) == 1);
        TEST(*(cle_t*)value(at(&non_livrables, 4)) == 5);

        TEST(size(depassent_solde) == 1);
        TEST(*(cle_t*)value(at(&depassent_solde, 0)) == 7);


        // Une commande invalide dû à un trop petit solde, devient valide après crédité 
        // suffisament d'euros au solde.
        // De plus, ces items viendront de deux restaurants à la fois.
        clear(&items);
        clear(&non_livrables);
        clear(&depassent_solde);
        ixi = 1; push_back(&items, &ixi);
        ixi = 2; push_back(&items, &ixi);
        ixi = 3; push_back(&items, &ixi);
        ixi = 4; push_back(&items, &ixi);
        ixi = 5; push_back(&items, &ixi);

        TEST(le_valider_commande(1, &items, &non_livrables, &depassent_solde) == false);
        TEST(size(items) == 0);
        TEST(size(non_livrables) == 0);
        TEST(size(depassent_solde) == 5);
        TEST(*(cle_t*)value(at(&depassent_solde, 0)) == 1);
        TEST(*(cle_t*)value(at(&depassent_solde, 4)) == 5);

        le_crediter_solde_client(1, 100);
        clear(&items);
        clear(&non_livrables);
        clear(&depassent_solde);
        ixi = 1; push_back(&items, &ixi);
        ixi = 2; push_back(&items, &ixi);
        ixi = 3; push_back(&items, &ixi);
        ixi = 4; push_back(&items, &ixi);
        ixi = 5; push_back(&items, &ixi);

        TEST(le_valider_commande(1, &items, &non_livrables, &depassent_solde) == true);
        TEST(size(items) == 5);
        TEST(*(cle_t*)value(at(&items, 0)) == 1);
        TEST(*(cle_t*)value(at(&items, 4)) == 5);
        TEST(size(non_livrables) == 0);
        TEST(size(depassent_solde) == 0);

        destroy(&items);
        destroy(&non_livrables);
        destroy(&depassent_solde);

        fermeture_db("build/test-db");
    }

    // Tests des commandes et débit et crédit des soldes.
    // Pour une livraison, un livreur gagne 3 euros, soustraits du total.
    {
        ouverture_db("build/test-db");

        vector items = make_vector(sizeof(cle_t), 0);
        cle_t ixi;

        // Une commande remplie par un seul restaurant (3) et livrée par un seul livreur (3).
        ixi = 6; push_back(&items, &ixi);
        ixi = 7; push_back(&items, &ixi);
        int total_commande = le_total_commande(&items);

        le_crediter_solde_client(2, total_commande);
        int solde_client_2_avant = le_cherche_client_i(2)->solde;
        int solde_livreur_3_avant = le_cherche_livreur_i(3)->solde;
        int solde_restaurant_3_avant = le_cherche_restaurant_i(3)->solde;

        le_passer_commande(2, &items);

        TEST(solde_client_2_avant - total_commande == le_cherche_client_i(2)->solde);
        TEST(solde_livreur_3_avant + 3 == le_cherche_livreur_i(3)->solde);
        TEST(solde_restaurant_3_avant + total_commande - 3 == le_cherche_restaurant_i(3)->solde);


        // Une commande remplie par deux restaurants (1 et 2) et livrée par un seul livreur (2).
        // Le livreur touchera deux commissions de trois euros chacune.
        clear(&items);
        ixi = 1; push_back(&items, &ixi);
        ixi = 2; push_back(&items, &ixi);
        ixi = 3; push_back(&items, &ixi);
        ixi = 4; push_back(&items, &ixi);
        ixi = 5; push_back(&items, &ixi);
        total_commande = le_total_commande(&items);

        le_crediter_solde_client(1, total_commande);
        int solde_client_1_avant = le_cherche_client_i(1)->solde;
        int solde_restaurant_1_avant = le_cherche_restaurant_i(1)->solde;
        int solde_restaurant_2_avant = le_cherche_restaurant_i(2)->solde;
        int solde_livreur_2_avant = le_cherche_livreur_i(2)->solde;

        le_passer_commande(1, &items);

        TEST(solde_client_1_avant - total_commande == le_cherche_client_i(1)->solde);
        TEST(solde_livreur_2_avant + 3 + 3 == le_cherche_livreur_i(2)->solde);
        // Le reste du total revient à cahque restaurant, dépendement de ce qu'il a fourni pour la commande.
        TEST(solde_restaurant_1_avant + 47 == le_cherche_restaurant_i(1)->solde);
        TEST(solde_restaurant_2_avant + 7 == le_cherche_restaurant_i(2)->solde);


        // Une commande remplie par deux restaurants (2, 3) et livrée par deux livreurs (2, 3).
        // Chaque livreur touchera une commission de trois euros.
        clear(&items);
        ixi = 2; push_back(&items, &ixi);
        ixi = 3; push_back(&items, &ixi);
        ixi = 6; push_back(&items, &ixi);
        ixi = 7; push_back(&items, &ixi);
        total_commande = le_total_commande(&items);

        le_crediter_solde_client(4, total_commande);
        int solde_client_4_avant = le_cherche_client_i(4)->solde;
            solde_restaurant_2_avant = le_cherche_restaurant_i(2)->solde;
            solde_restaurant_3_avant = le_cherche_restaurant_i(3)->solde;
            solde_livreur_2_avant = le_cherche_livreur_i(2)->solde;
            solde_livreur_3_avant = le_cherche_livreur_i(3)->solde;

        le_passer_commande(4, &items);

        TEST(solde_client_4_avant - total_commande == le_cherche_client_i(4)->solde);
        TEST(solde_livreur_2_avant + 3 == le_cherche_livreur_i(2)->solde);
        TEST(solde_livreur_3_avant + 3 == le_cherche_livreur_i(3)->solde);
        // Le reste du total revient à chaque restaurant, dépendamment de ce qu'il a fourni pour la commande.
        TEST(solde_restaurant_2_avant + 7 == le_cherche_restaurant_i(2)->solde);
        TEST(solde_restaurant_3_avant + 17 == le_cherche_restaurant_i(3)->solde);

        destroy(&items);

        fermeture_db("build/test-db");
    }


    return tests_total - tests_successful;
}
