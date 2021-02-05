import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;

public class Parser {
    public ArrayList<String> parseForEncoder(String fileName) throws java.io.IOException {
        ArrayList<String> result = new ArrayList<>();
        BufferedReader in = new BufferedReader(new FileReader(fileName));
        String str;

        while((str = in.readLine()) != null){
            for(String item : str.split(" ")){
                if(!item.equals(" ")) result.add(item);
            }
        }
        in.close();
        return result;
    }

    public ArrayList<String> parseForDecoder(String fileName) throws java.io.IOException{
        String morseCodeSpace = "   ";

        ArrayList<String> result = new ArrayList<>();
        BufferedReader in = new BufferedReader(new FileReader(fileName));
        String str;

        while((str = in.readLine()) != null){
            for(String item : str.split(morseCodeSpace)){
                if(!item.equals(" ")) result.add(item);
            }
        }

        in.close();
        return result;
    }
}
