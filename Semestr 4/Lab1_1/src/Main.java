public class Main {

    public static void main(String[] args) throws Exception {

        if (0 == args.length) {
            System.err.println("No arguments");
            return;
        }

        try {
            WordCounter counter = new WordCounter();
            counter.run(args[0]);
        } catch (Exception e) {
            System.err.println("ERROR: " + e.getMessage());
        }
    }
}