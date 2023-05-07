CREATE TABLE IF NOT EXISTS USERS(
		ID INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,
		USERNAME TEXT NOT NULL UNIQUE,
  		PASSWORD TEXT NOT NULL,
		EMAIL TEXT NOT NULL UNIQUE
		SCORE INTEGER);

		
CREATE TABLE IF NOT EXISTS CATEGORIES(
		ID INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,
		PERMISSION BOOLEAN NOT NULL,
		CREATOR_ID INTEGER NOT NULL,
		NAME TEXT NOT NULL UNIQUE,
	
		FOREIGN KEY(CREATOR_ID) REFERENCES USERS(ID) ON DELETE CASCADE);

		
CREATE TABLE IF NOT EXISTS QUESTIONS(
		QUESTION_ID INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,
		CATEGORY_ID INTEGER NOT NULL,
		
		QUESTION TEXT NOT NULL,
		CORRECT_ANSWER_INDEX INTEGER NOT NULL,
		FIRST_ANSWER TEXT NOT NULL,
		SECOND_ANSWER TEXT NOT NULL,
		THIRD_ANSWER TEXT NOT NULL,
		FOURTH_ANSWER TEXT NOT NULL,
		
		FOREIGN KEY(CATEGORY_ID) REFERENCES CATEGORIES(ID) ON DELETE CASCADE);


CREATE TABLE IF NOT EXISTS HISTORY(
		USER_ID INTEGER NOT NULL,
		CATEGORY_ID INTEGER NOT NULL,
		RANK INTEGER  NOT NULL,
		AVERAGE_TIME  DOUBLE NOT NULL,
		NUMBER_OF_ANSWERS  INTEGER NOT NULL,
		NUMBER_OF_CORRECT_ANSWERS  INTEGER NOT NULL,
		CREATION_DATE DATETIME DEFAULT(getdate()), 
		
		FOREIGN KEY(CATEGORY_ID) REFERENCES CATEGORIES(ID) ON DELETE CASCADE,
		FOREIGN KEY(USER_ID) REFERENCES USERS(ID) ON DELETE CASCADE);


CREATE TABLE IF NOT EXISTS STATISTICS(
		USER_ID INTEGER NOT NULL UNIQUE,

		AVERAGE_TIME  DOUBLE NOT NULL,
		NUMBER_OF_GAMES  INTEGER NOT NULL,
		NUMBER_OF_ANSWERS  INTEGER NOT NULL,
		NUMBER_OF_CORRECT_ANSWERS  INTEGER NOT NULL,
		
		FOREIGN KEY(USER_ID) REFERENCES USERS(ID) ON DELETE CASCADE);