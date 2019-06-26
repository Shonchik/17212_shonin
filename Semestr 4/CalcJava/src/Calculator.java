import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Logger;


public class Calculator {


    private static final Logger log = (Logger) Logger.getLogger(String.valueOf(Calculator.class));

    public static void main(String[] args) {

        String commandStr;

        if (2 == args.length) {
            try (BufferedReader fileReader = new BufferedReader(new FileReader(args[1]))) {
                while (null != (commandStr = fileReader.readLine())) {
                    runCommand(commandStr);
                }

            } catch (Exception e) {
                System.err.println("ERROR: " + e.getMessage());
            }
        } else {
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
                while (true) {

                    commandStr = reader.readLine();
                    if (commandStr.equalsIgnoreCase("exit")) {
                        break;
                    }

                    runCommand(commandStr);
                }
            } catch (Exception e) {
                System.err.println("ERROR: " + e.getMessage());
            }
        }
    }

    private static void runCommand(String commandStr) {
        if (!commandStr.startsWith("#")) {
            try {
                commandStr = commandStr.trim().replaceAll("\\s+", " ");

                List<String> commandList = new ArrayList<String>(Arrays.asList(commandStr.split(" ")));

                CommandClass cmd = Factory.createCommand(commandList);

                if (null != cmd) {
                    cmd.run();
                }

            } catch (Exception er) {
                System.out.println("ERROR with command run: " + er);
            }
        }
    }
}