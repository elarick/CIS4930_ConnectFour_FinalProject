import static org.junit.Assert.*;

import org.junit.Test;


public class AiTest {

	@Test
	public void Test() {
		/*
1 2 3 4 5 6 7 
. . . . . . . 
. . . . . . . 
. . . O . . . 
. . . X X . . 
. O . X X O . 
. O . X X O . 

		 */
		Board board = new Board(6,7,4);
		board.makeMoveAI(1);
		board.makeMoveAI(1);
		board.makeMoveAI(5);
		board.makeMoveAI(5);
		board.makeMovePlayer(3);
		board.makeMovePlayer(3);
		board.makeMovePlayer(3);
		board.makeMoveAI(3);
		board.makeMovePlayer(4);
		board.makeMovePlayer(4);
		board.makeMovePlayer(4);
		
		Ai ai = new Ai(board);
		assertEquals(4, ai.makeTurn());
	}

}
