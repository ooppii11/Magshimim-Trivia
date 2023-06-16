class Room {
  final int id;
  final String name;
  final int categorieId;
  final int maxPlayers;
  final int numOfQuestionsInGame;
  final int timePerQuestion;
  final bool isActive;

  Room(this.id, this.name, this.categorieId, this.maxPlayers,
      this.numOfQuestionsInGame, this.timePerQuestion, this.isActive);

  int getId() {
    return this.id;
  }

  String getName() {
    return name;
  }

  int getNumOfQuestionsInGame() {
    return numOfQuestionsInGame;
  }

  int getTimePerQuestion() {
    return timePerQuestion;
  }

  bool getIsActive() {
    return isActive;
  }
}
