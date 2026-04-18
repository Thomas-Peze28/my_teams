# MyTeams - Roadmap de Développement

**Date**: Avril 2026  
**État du Projet**: En cours de développement (Phase d'implémentation)  
**Langage**: C/C++20

---

## 📊 État Actuel du Projet

### ✅ Complété

#### Infrastructure de Base
- [x] Structure de répertoires organisée
- [x] Makefile principal et makefile par sous-module (client/server)
- [x] Système de build avec compilation correcte (`make all`)
- [x] Architecture modulaire avec séparation des responsabilités

#### Documentation & Protocole
- [x] Fichier `MyTeams_Protocol.txt` avec spécifications du protocole
- [x] Format de communication établi (codes 3 chiffres + keywords)
- [x] Intégration des libraries de logging (`logging_client.h`, `logging_server.h`)

#### Sous-structures de Données
- [x] Interface `IContainer` pour objet hiérarchiques
- [x] Classes déclarées: `Hub`, `Team`, `Channel`, `Thread`, `User`, `Client`
- [x] Classes de support: `Command`, `Parser`, `PollFD`, `NetworkServer`, `Server`
- [x] Headers générés avec déclarations de base

#### Points d'Entrée
- [x] `server/src/main.cpp` - Point d'entrée serveur
- [x] `client/src/main.cpp` - Point d'entrée client
- [x] Arguments CLI parsés (help, port, IP)

---

### ❌ En cours / À faire

#### **PHASE 1: Infrastructure Côté Serveur (Priorité: CRITIQUE)**

##### 1.1 Structure de Données (50% complétée)
- [ ] **Classe `User`**
  - [ ] Champs: `uuid`, `username`, `creation_date`, `status` (online/offline)
  - [ ] Méthodes: getters/setters, sérialisation
  - [ ] Implémentation du serialization en JSON ou binaire

- [ ] **Classe `Team`**
  - [x] Déclaration minimale
  - [ ] Champs complets: `uuid`, `name`, `description`, `channels[]`, `members[]`
  - [ ] Méthodes: `addChannel()`, `removeChannel()`, `addMember()`, `removeMember()`
  - [ ] Implémentation de `create()`, `list()`, `info()` (override IContainer)

- [ ] **Classe `Channel`**
  - [x] Déclaration minimale
  - [ ] Champs: `uuid`, `name`, `description`, `threads[]`, `team_uuid`
  - [ ] Méthodes: `addThread()`, `removeThread()`
  - [ ] Implémentation de `create()`, `list()`, `info()`

- [ ] **Classe `Thread`**
  - [x] Déclaration minimale
  - [ ] Champs: `uuid`, `title`, `message`, `author_uuid`, `replies[]`, `creation_date`
  - [ ] Implémentation de `create()`, `list()`, `info()`

- [ ] **Classe `Message` (pour messages privés)**
  - [ ] Champs: `from_uuid`, `to_uuid`, `content`, `timestamp`
  - [ ] Stockage pair-à-pair

##### 1.2 Système de Gestion des Clients
- [ ] **Classe `Client` (serveur)**
  - [ ] Champs: `socket_fd`, `user_uuid`, `is_authenticated`, `subscribed_teams[]`, `context` (current team/channel/thread)
  - [ ] Implémentation de `send()` (envoyer données au client)
  - [ ] Implémentation de `receive()` (recevoir commandes du client)

##### 1.3 Système de Communication Réseau
- [x] Classe `NetworkServer` déclarée
  - [ ] Initialisation du socket serveur
  - [ ] Liaison (`bind`) et écoute (`listen`)
  - [ ] Acceptation des connexions entrantes
  - [ ] Gestion des erreurs réseau

- [x] Classe `PollFD` déclarée
  - [ ] Maintien du tableau `pollfd[]`
  - [ ] Ajout/suppression dynamique de clients
  - [ ] Appels à `poll()` pour multiplexing I/O
  - [ ] Gestion des événements POLLIN/POLLOUT

##### 1.4 Parser & Command Handler
- [ ] **Classe `Parser`**
  - [ ] Parsing des commandes reçues du client
  - [ ] Validation de la syntaxe (guillemets, arguments requis)
  - [ ] Extraction des arguments
  - [ ] Construction d'objets `CommandData`

- [ ] **Classe `Command`**
  - [ ] Implémentation complète de chaque commande:
    - [ ] `/login [username]`
    - [ ] `/logout`
    - [ ] `/users` (filtrée selon connexion)
    - [ ] `/user [uuid]`
    - [ ] `/send [uuid] [message]`
    - [ ] `/messages [uuid]`
    - [ ] `/subscribe [team_uuid]`
    - [ ] `/subscribed [?team_uuid]`
    - [ ] `/unsubscribe [team_uuid]`
    - [ ] `/use [?team_uuid] [?channel_uuid] [?thread_uuid]`
    - [ ] `/create` (context-aware)
    - [ ] `/list` (context-aware)
    - [ ] `/info` (context-aware)

##### 1.5 Système de Sauvegarde/Chargement
- [ ] Implémentation `Server::save()`
  - [ ] Sérialisation des users
  - [ ] Sérialisation des teams + channels + threads
  - [ ] Sérialisation des messages privés
  - [ ] Format de fichier choisi (JSON/CSV/binaire)

- [ ] Implémentation `Server::loadUsers()`
  - [ ] Désérialisation depuis fichier
  - [ ] Réindexation des structures

- [ ] Implémentation `Server::loadTeams()`
  - [ ] Chargement hiérarchie complète
  - [ ] Vérification d'intégrité

- [ ] Gestion du signal `SIGINT` (Ctrl+C)
  - [ ] Appel automatique à `save()` avant exit

##### 1.6 Système d'Événements & Notifications
- [ ] Broadcasting des événements aux clients connectés
  - [ ] Événement: nouvelle équipe créée
  - [ ] Événement: nouvel utilisateur connecté
  - [ ] Événement: nouveau canal créé
  - [ ] Événement: nouveau fil créé
  - [ ] Événement: nouveau commentaire
  - [ ] Événement: nouveau message privé reçu

- [ ] Filtrage par abonnement (subscription)
  - [ ] Les clients ne reçoivent que les événements de teams auxquels ils sont abonnés

---

#### **PHASE 2: Client CLI (Priorité: HAUTE)**

##### 2.1 Communication avec Serveur
- [ ] **Classe `Client` (client)**
  - [x] Déclaration minimale
  - [ ] `connectToServer()` - établir connexion TCP
  - [ ] `handleServerInput()` - recevoir réponses du serveur (avec gestion du timeout/poll)
  - [ ] `handleUserInput()` - lire stdin (prompt)
  - [ ] `processServerMessage()` - parser réponse du serveur
  - [ ] `extractArgs()` - extraction d'arguments depuis réponse

##### 2.2 Parser de Commandes Locales
- [ ] Parsing des commandes utilisateur depuis stdin
- [ ] Validation des guillemets
- [ ] Validation du nombre d'arguments
- [ ] Gestion des erreurs locales

##### 2.3 Gestion du Contexte
- [ ] Stockage du contexte courant (team_uuid, channel_uuid, thread_uuid)
- [ ] Adaptation des commandes `/create`, `/list`, `/info`

##### 2.4 Implémentation de Chaque Commande
- [ ] Communication avec le serveur
- [ ] Attente des réponses
- [ ] Affichage avec library `logging_client.h` (les seules fonctions autorisées)
- [ ] Gestion d'erreurs serveur

---

#### **PHASE 3: Intégration & Testing (Priorité: MOYENNE)**

##### 3.1 Tests de Communication
- [ ] Test connexion client-serveur
- [ ] Test parsing des commandes
- [ ] Test envoi/réception des données
- [ ] Test avec plusieurs clients simultanees

##### 3.2 Tests Fonctionnels
- [ ] Création d'équipe, de canaux, de fils, de commentaires
- [ ] Gestion des utilisateurs
- [ ] Messages privés
- [ ] Abonnement/désabonnement
- [ ] Contexte en cours (/use)

##### 3.3 Tests de Sauvegarde
- [ ] Sauvegarde au shutdown (Ctrl+C)
- [ ] Rechargement au redémarrage
- [ ] Vérification d'intégrité des données

##### 3.4 Tests de Sécurité
- [ ] Non-authentifié: impossible de voir les utilisateurs connectés
- [ ] Non-abonné à une team: impossible de créer un fil
- [ ] Non-abonné à une team: n'obtient pas les événements d'équipe

---

## 🎯 Feuille de Route Détaillée (Phases & Étapes)

### **Étape 0: PRÉPARATION (2-3 heures)**

1. **Documenter les champs de chaque classe**
   - Créer un schéma de données détaillé
   - Décider du format de sérialisation (JSON recommandé avec `nlohmann/json`)

2. **Définir les codes de réponse du serveur**
   - Codes succès (2xx)
   - Codes erreurs (4xx, 5xx)
   - Créer une énumération ou constantes

3. **Organiser les includes & dépendances**
   - Vérifier que `-luuid` est bien linké
   - Vérifier la lib logging
   - Ajouter JSON si nécessaire

---

### **Étape 1: Implémentation des Structures de Données (4-5 heures)**

#### Ordre recommandé:

1. `User.hpp / User.cpp`
   - Champs: uuid, username, creation_date, status
   - Méthodes getters/setters
   - Sérialisation

2. `Thread.cpp` (finir implémentation)
   - Champs: uuid, title, message, author_uuid, replies, creation_date
   - Méthodes CRUD

3. `Channel.cpp` (finir implémentation)
   - Champs: uuid, name, description, threads, team_uuid
   - Méthodes CRUD

4. `Team.cpp` (finir implémentation)
   - Champs: uuid, name, description, channels, members
   - Méthodes CRUD

5. `Hub.cpp`
   - Container pour tous les teams
   - Implémentation de `create()`, `list()`, `info()`

6. `Message.hpp / Message.cpp` (classe pour messages privés)
   - Champs: from_uuid, to_uuid, content, timestamp
   - Getters/setters

---

### **Étape 2: Gestion des Clients Serveur (2-3 heures)**

1. Finir `Client.cpp` (côté serveur)
   - Initialisation avec socket descriptor
   - Implémentation `send()`
   - Implémentation `receive()`

2. Implémentation `NetworkServer.cpp`
   - Socket creation and configuration
   - bind() + listen()
   - accept() dans la boucle principale

3. Implémentation `PollFD.cpp`
   - Gestion du tableau pollfd
   - Méthodes `addClient()`, `deleteClient()`
   - Maintien du serveur socket + client sockets

---

### **Étape 3: Parser & Command Handler (3-4 heures)**

1. Implémentation `Parser.cpp`
   - Parsing de chaine de caractères
   - Extraction des arguments (avec validation guillemets)
   - Construction de CommandData

2. Implémentation `Command.cpp`
   - Chaque commande dans une méthode séparée
   - Validation des arguments
   - Interaction avec Hub, Team, Channel, Thread, Message
   - Envoi de réponses via `client.send()`

---

### **Étape 4: Server Main Loop (2-3 heures)**

1. Implémentation `Server::runServer()`
   - Boucle principal avec `poll()`
   - Gestion du serveur socket (nouvelles connexions)
   - Gestion des clients (lectures/écritures)
   - Appel du Parser quand il y a des données

2. Implémentation `Server::initServer(uint16_t port)`
   - Appel NetworkServer
   - Appel PollFD
   - Chargement des données (loadUsers, loadTeams, etc.)

3. Gestion du signal SIGINT
   - Finir `Server::signalHandler()`
   - Appel à `save()` avant shutdown

---

### **Étape 5: Sauvegarde & Chargement (3-4 heures)**

1. Choisir format (recommandé: JSON avec `nlohmann/json`)
   - Structure: `/saves/users.json`, `/saves/teams/`, etc.

2. Implémentation:
   - `Server::save()` - sérialisation complète
   - `Server::loadUsers()` - désérialisation users
   - `Server::loadTeams()` - désérialisation teams hiérarchie
   - `Server::loadChannels()` - helper pour teams
   - `Server::loadThreads()` - helper pour channels

3. Gestion d'erreurs
   - Fichiers manquants (premier lancement)
   - Corruption de données

---

### **Étape 6: Système d'Événements (2-3 heures)**

1. Créer une queue/système de notifications
   - Chaque client a sa liste d'événements

2. Broadcasting aux clients abonnés
   - Filtre par team subscription

3. Implémentation des événements serveur
   - Nouvel utilisateur, nouvelle team, nouveau channel, etc.

4. Intégration dans Command handler
   - Après chaque création/modification, envoyer événements

---

### **Étape 7: Implémentation Client CLI (5-6 heures)**

#### 7.1: Communication Réseau (1-2 heures)
1. `Client::connectToServer()` - connexion TCP
2. `Client::handleServerInput()` - réception responses
3. `Client::handleUserInput()` - stdin avec prompt
4. Intégration avec `poll()` pour non-blocking I/O

#### 7.2: Parser Local (1 heure)
1. Tokenization des commandes
2. Validation guillemets
3. Vérification nombre arguments

#### 7.3: Gestion Contexte (30 min)
1. Variables: team_uuid, channel_uuid, thread_uuid
2. Adaptation des commandes selon contexte

#### 7.4: Implémentation de Chaque Commande (3-4 heures)
1. Pour chaque commande:
   - Construire message à envoyer au serveur
   - Attendre réponse
   - Parser réponse
   - Afficher avec `logging_client.h`

---

### **Étape 8: Testing Complet (3-4 heures)**

1. Tests unitaires basiques
2. Tests d'intégration (client-serveur)
3. Tests de sauvegarde/chargement
4. Tests de sécurité (authentification, abonnement)
5. Tests avec plusieurs clients
6. Tests de robustesse (Ctrl+C, déconnexions, etc.)

---

## 📋 Checklist de Validation

### Par Étape:

- [ ] Étape 0: Préparation documentée
- [ ] Étape 1: Structures de données complètes et compilables
- [ ] Étape 2: Gestion des clients sans erreurs mémoire
- [ ] Étape 3: Parser et Command handler fonctionnels
- [ ] Étape 4: Serveur démarre et accepte connexions
- [ ] Étape 5: Save/Load fonctionne correctement
- [ ] Étape 6: Événements propagés correctement
- [ ] Étape 7: Client CLI peut envoyer et recevoir
- [ ] Étape 8: Tous les tests passent

### Finale:

- [ ] `make all` compile sans erreurs/warnings
- [ ] `make clean` nettoie les objet files
- [ ] `make fclean` supprime les binaires
- [ ] `make re` recompile complètement
- [ ] Binaires générés dans la racine du projet
- [ ] Server peut gérer au moins 10 clients simultanés
- [ ] Data persist après redémarrage
- [ ] Toutes les 20+ commandes fonctionnent

---

## 🔍 Points d'Attention

### Bugs Courants à Éviter

1. **Memory Leaks**
   - Utiliser `std::unique_ptr` systématiquement
   - Vérifier avec valgrind si besoin

2. **File Descriptors**
   - Toujours fermer les sockets correctement
   - Gérer les erreurs poll()

3. **Parsing**
   - Validations strictes des guillemets
   - Limites de longueur (NAME=32, DESC=255, BODY=512)

4. **Concurrence (pseudo)**
   - Pas de vraix concurrence (pas de fork/threads)
   - Mais attention à l'état client lors de perte connexion

5. **Sauvegarde**
   - Atomicité: ne pas écrire pendant qu'on lit
   - Backups: garder ancienne version pendant l'écriture

---

## 📚 Ressources Utiles

- `man 7 poll` - pour la gestion multi-clients
- `man 3 uuid` - génération d'UUIDs
- `man 2 socket, connect, send, recv` - API network
- MyTeams_Protocol.txt - spécifications complètes

---

## ⏱️ Estimation de Temps Total

| Étape | Estimation | Notes |
|-------|-----------|-------|
| 0 | 2-3h | Préparation |
| 1 | 4-5h | Structures données |
| 2 | 2-3h | Clients serveur |
| 3 | 3-4h | Parser/Commands |
| 4 | 2-3h | Server loop |
| 5 | 3-4h | Save/Load |
| 6 | 2-3h | Événements |
| 7 | 5-6h | Client CLI |
| 8 | 3-4h | Testing |
| **TOTAL** | **27-35h** | **~1 semaine à temps plein** |

---

## 🚀 Prochaines Actions Immédiates

1. **Réviser MyTeams_Protocol.txt** pour codes de réponse exacts
2. **Créer les fichiers User.hpp/User.cpp**
3. **Créer schéma JSON** pour sérialisation
4. **Commencer Étape 1** (structures de données)

---

*Généré: Avril 2026*  
*Dernière mise à jour: [À remplir]*
