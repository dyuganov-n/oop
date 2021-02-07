import java.io.IOException;
import java.util.Locale;
import java.util.Scanner;

public class MorseCode {
    public void run() throws IOException {
        String command, inputFileName;
        try (Scanner in = new Scanner(System.in)) {
            System.out.println("Enter command and file name.");
            command = in.next().toLowerCase(Locale.ROOT);
            inputFileName = in.next();
        }

        Parser parser = new Parser();
        Alphabet alphabet = new Alphabet("src/resources/alphabet.txt");

        if(command.equals("decode")){
            MorseDecoder decoder = new MorseDecoder(alphabet);
            String outputFileName = "decode_result.txt";
            decoder.decode(parser.parseForDecoder(inputFileName), outputFileName);
            System.out.println("Decode completed. Output file: " + outputFileName);
        }
        else if(command.equals("code")){
            String outputFileName = "encode_result.txt";
            MorseEncoder encoder = new MorseEncoder(alphabet);
            encoder.encode(parser.parseForEncoder(inputFileName), outputFileName);
            System.out.println("Encode completed. Output file: " + outputFileName);
        }
        else{
            System.out.println("Wrong command.");
        }
    }
}
