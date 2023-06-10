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
    return this.getId();
  }

  String getName() {
    return this.name;
  }

  int getNumOfQuestionsInGame() {
    return this.numOfQuestionsInGame;
  }

  int getTimePerQuestion() {
    return this.timePerQuestion;
  }

  bool getIsActive() {
    return this.isActive;
  }
}
