import java.util.Scanner;

public final class In {
	final static Scanner scanner = new Scanner(System.in);

	public static int getInput(int from, int to) {
		int result = 0;
		boolean noException;
		String inputString;
		do {
			noException = true;
			inputString = scanner.nextLine();
			try {
				result = Integer.parseInt(inputString);
			} catch (NumberFormatException e) {
				noException = false;
			}
		} while (result < from || result > to || !noException);
		return result;
	}

	public static boolean getBoolean(String trueInd, String falseInd) {
		String inputString;
		do {
			inputString = scanner.nextLine(); 
		} while (!inputString.equals(trueInd) && !inputString.equals(falseInd));
		return inputString.equals(trueInd);
	}
}
