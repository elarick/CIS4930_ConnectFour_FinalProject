import static org.junit.Assert.*;

import org.junit.Test;

public class BoardTest {

	@Test
	public void testGetWinner() {
		// X
		// OX
		// XOX
		// XXOX
		Board board = new Board(6, 7, 4);
		board.makeMovePlayer(1);
		board.makeMovePlayer(2);
		board.makeMoveAI(3);
		board.makeMovePlayer(4);
		board.makeMovePlayer(1);
		board.makeMoveAI(2);
		board.makeMovePlayer(3);
		board.makeMoveAI(1);
		board.makeMovePlayer(2);
		board.makeMovePlayer(1);
		
		assertEquals(board.PLAYER, board.getWinner());
	}

	@Test
	public void testGetWinner2() {
		// X
		// OX
		// XOX
		// XXOX
		Board board = new Board(6, 7, 4);
		board.makeMovePlayer(0);
		board.makeMovePlayer(1);
		board.makeMoveAI(2);
		board.makeMovePlayer(3);
		board.makeMovePlayer(0);
		board.makeMoveAI(1);
		board.makeMovePlayer(2);
		board.makeMoveAI(0);
		board.makeMovePlayer(1);
		board.makeMovePlayer(0);
		
		assertEquals(board.PLAYER, board.getWinner());
	}
}
