CREATE TABLE IF NOT EXISTS Scores (
	PlayerName TEXT,
	Score INTEGER
);

-- ref https://www.geeksforgeeks.org/sqlite-indexes/
-- Index scores so we can quickly sort the leaderboard
CREATE INDEX IF NOT EXISTS ScoreIndex ON Scores(Score);

