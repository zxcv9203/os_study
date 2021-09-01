public class ThreadExample3 {
	public static final void main(String[] args) {
		Runnable task = () -> {
			try {
				while (true) {
					System.out.println("Hello, Lambda Runnable!");
					Thread.sleep(500);
				}
			}
			catch (InterruptException ie) {
				System.out.println("I'm interrupted");
			}
		};
		Thread thread = new Thread(task);
		thread.start();
		System.out.println("Hello, My Lambda Child!");
	}
}