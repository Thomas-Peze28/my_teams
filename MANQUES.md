# MyTeams - Résumé des Manques & Actions Critiques

**État**: ~30-40% du projet complété

---

## 🔴 Manques Critiques (Bloquer la compilation/exécution)

### Serveur
1. **Implémentations vides ou incomplètes:**
   - `Server.cpp` - runServer(), loadUsers(), loadTeams(), loadChannels(), loadThreads()
   - `Command.cpp` - toutes les méthodes de commandes
   - `Parser.cpp` - parsing et handling des messages
   - `NetworkServer.cpp` - initialisation socket et bind/listen
   - `PollFD.cpp` - gestion du poll et des clients

2. **Classes manquantes:**
   - `User` (plus important que tout!) - stockage/getters/setters/serialization
   - `Message` - pour les échanges privés
   
3. **Gestion des données:**
   - Aucun système de sérialisation/désérialisation
   - Aucun format de stockage défini
   - Aucun chargement au démarrage

### Client
1. **Implémentations vides ou incomplètes:**
   - `Client.cpp` - connectToServer(), handleServerInput(), handleUserInput(), processServerMessage()
   - Parser local des commandes utilisateur
   - Gestionnaire de contexte (/use team/channel/thread)

2. **Communication réseau:**
   - Pas de vraie connexion TCP
   - Pas de boucle poll pour non-blocking I/O
   - Pas de parsing des réponses serveur

---

## 🟡 Manques Importants (Non-bloquants mais essentiels)

- [ ] Gestion du signal SIGINT (Ctrl+C) → save
- [ ] Système d'événements/notifications
- [ ] Broadcasting aux clients abonnés
- [ ] Filtrage des événements par team subscription
- [ ] Validation stricte des arguments (longueurs, guillemets)
- [ ] Gestion d'erreurs réseau et reconnexion

---

## 🟢 Partiellement Complété

- ✅ Architecture générale
- ✅ Headers des classes
- ✅ Makefile et build system
- ✅ Logging library intégrée
- ✅ Interfaces et héritage (IContainer)
- ⚠️ Protocol documentation (besoin de codes réponse exacts)

---

## 📊 Impact par Catégorie

| Catégorie | % Complété | Impact | État |
|-----------|-----------|--------|------|
| **Architecture** | 80% | Faible | Bon |
| **Réseau (Serveur)** | 10% | Critique | À faire |
| **Données (Serveur)** | 30% | Critique | À faire |
| **Commands (Serveur)** | 5% | Critique | À faire |
| **Réseau (Client)** | 10% | Critique | À faire |
| **Commands (Client)** | 5% | Critique | À faire |
| **Save/Load** | 0% | Haute | À faire |
| **Événements** | 0% | Moyenne | À faire |
| **Logging** | 100% | Faible | Usable |

---

## ⚡ Top 5 Priorités IMMÉDIATES

1. **Créer classe `User` complète** (2h)
   - UUID, username, status, dates
   - Headers + implémentation
   - C'est le fondement de tout

2. **Implémenter `NetworkServer` & `PollFD`** (3h)
   - Socket server, bind, listen, accept
   - Multiplexing poll()
   - C'est la base réseau

3. **Implémenter `Server::runServer()`** (2h)
   - Boucle principale avec poll
   - Gestion des connexions
   - C'est le cœur du serveur

4. **Implémenter `Client::connectToServer()` et boucle I/O** (2h)
   - Connexion TCP
   - Boucle avec poll() pour non-blocking
   - C'est le démarrage du client

5. **Implémenter `Parser` + `Command` pour commandes communes** (4h)
   - /help, /login, /logout, /users
   - C'est la preuve que tout fonctionne

---

## 🎯 Sprint Immédiat (Semaine 1)

**Jour 1-2**: Infrastructure réseau
- User.cpp complète
- NetworkServer.cpp + PollFD.cpp
- Server::runServer() basique

**Jour 3**: Client basique
- Client::connectToServer()
- Boucle I/O simple

**Jour 4-5**: Commands minimales
- Parser.cpp pour commands simple
- Command.cpp pour /help, /login, /logout
- Tester client ↔ serveur

**Jour 6-7**: Données persistantes
- Implémentation save/load
- Hub.cpp (Team, Channel, Thread)
- Tests multiples clients

---

## 📝 Format Proposé pour Données

**JSON** (recommandé):
```
saves/
├── users.json       # Tous les utilisateurs
├── teams/
│   ├── [team_uuid].json      # Team + channels
│   └── channels/
│       └── [channel_uuid].json # Channel + threads
└── messages/
    └── [user1_user2].json    # Messages privés
```

---

## 🔗 Dépendances Client-Serveur

```
User (foundational)
├── Team
│   ├── Channel
│   │   └── Thread
│   │       └── Comment
│   └── Members
├── Direct Messages
└── Subscriptions
```

**Ordre d'implémentation recommandé**: User → Team → Channel → Thread

---

## ✅ Checklist pour Démarrage

- [ ] User.hpp/cpp créés et compilent
- [ ] NetworkServer.cpp lit un port
- [ ] Server.cpp peut accepter une connexion
- [ ] Client.cpp peut se connecter
- [ ] Premier /login fonctionne d'un bout à l'autre

Une fois ces 5 points ✅, le reste devient incrémental et moins critique.
