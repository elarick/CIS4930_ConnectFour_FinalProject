import java.util.Random;

public class Main {
	static Random random = new Random();

	public static void main(String[] args) {
		p("Welcome to 4 wins!");
		p("------------------");
		p("");

		p("Do you want to set the board size? Default is 7x6 [Y/N]");
		int width = 7;
		int height = 6;
		if (In.getBoolean("Y", "N")) {
			p("Please enter the width of the board");
			width = In.getInput(0, 100);
			p("Please enter the height of the board");
			height = In.getInput(0, 100);
		}

		p("Do you want to set how many stones are needed? Default is 4 [Y/N]");
		int winLength = 4;
		if (In.getBoolean("Y", "N")) {
			p("Please enter the number of stones required to win");
			winLength =
					In.getInput(2, Math.max(
							width, height));
		}

		p("The game starts now");
		boolean turn = getRandomBoolean();
		if (turn) {
			p("You are first to go!");
		} else {
			p("Your opponent has the first move!");
		}

		Board board =
				new Board(height, width,
						winLength);
		Ai ai = new Ai(board);
		int column = 0;
		while (!board.hasWinner()
				&& !board.isTie()) {
			p("");
			p(board.toString());
			if (turn) {
				do {
					p("In which column do you want to place your stone?");
					column =
							In.getInput(1, width) - 1;
					if (!board
							.isValidMove(column)) {
						p("You cannot place your stone in that column!");
					}
				} while (!board
						.isValidMove(column));
				board.makeMovePlayer(column);
			} else {
				int aiColumn = ai.makeTurn();
				p("Your opponent placed in column "
						+ (aiColumn + 1));
			}
			turn = !turn;
		}

		p("");
		p(board.toString());
		if (board.playerIsWinner()) {
			p("You win! Congratulations!");
		} else if (board.isTie()) {
			p("It's a tie, I think that is the best you can do!");
		} else {
			p("You lose! Try again!");
		}
	}

	static void p(String text) {
		System.out.println(text);
	}

	static boolean getRandomBoolean() {
		return random.nextBoolean();
	}
}
