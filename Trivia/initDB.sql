INSERT INTO USERS(USERNAME, PASSWORD, EMAIL) VALUES("test1", "12345678", "test1@gmail.com");
INSERT INTO USERS(USERNAME, PASSWORD, EMAIL) VALUES("test2", "12345678", "test2@gmail.com");


INSERT INTO CATEGORIES(NAME, PERMISSION, CREATOR_ID) VALUES("Animals", "True", 1);


INSERT INTO QUESTIONS(
		CATEGORY_ID,
		QUESTION,
		CORRECT_ANSWER_INDEX, 
		FIRST_ANSWER, 
		SECOND_ANSWER,
		THIRD_ANSWER,
		FOURTH_ANSWER)
	VALUES(
		1, 
		"Which animal is known as man’s best friend?",
		1,
		"Cat",
		"Dog",
		"Snake",
		"mouse"
		);

INSERT INTO QUESTIONS(
		CATEGORY_ID,
		QUESTION,
		CORRECT_ANSWER_INDEX, 
		FIRST_ANSWER, 
		SECOND_ANSWER,
		THIRD_ANSWER,
		FOURTH_ANSWER)
	VALUES(
		1, 
		"What kind of fish is Nemo?",
		2,
		"Salmon",
		"Catfish",
		"Clownfish",
		"Shark"
		);
		

INSERT INTO QUESTIONS(
		CATEGORY_ID,
		QUESTION,
		CORRECT_ANSWER_INDEX, 
		FIRST_ANSWER, 
		SECOND_ANSWER,
		THIRD_ANSWER,
		FOURTH_ANSWER)
	VALUES(
		1, 
		"How many species of wild cats are there?",
		3,
		"55",
		"103",
		"35",
		"41"
		);
		
		
INSERT INTO QUESTIONS(
		CATEGORY_ID,
		QUESTION,
		CORRECT_ANSWER_INDEX, 
		FIRST_ANSWER, 
		SECOND_ANSWER,
		THIRD_ANSWER,
		FOURTH_ANSWER)
	VALUES(
		1, 
		"What is the name of the fastest land animal?",
		0,
		"Cheetah",
		"Turtle",
		"Gno",
		"Deer"
		);
		

INSERT INTO QUESTIONS(
		CATEGORY_ID,
		QUESTION,
		CORRECT_ANSWER_INDEX, 
		FIRST_ANSWER, 
		SECOND_ANSWER,
		THIRD_ANSWER,
		FOURTH_ANSWER)
	VALUES(
		1, 
		"What animal is known by the nickname 'sea cow'?",
		2,
		"Sea cow",
		"Seal",
		"Manatee",
		"Squid"
		);