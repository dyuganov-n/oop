import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class Alphabet {
    private Map<Character, String> map = null;

    public Alphabet(String fileName) throws java.io.IOException {
        final int expectedSpacePos = 1;

        BufferedReader in = new BufferedReader(new FileReader(fileName));
        map = new HashMap<Character, String>();
        String str;

        while((str = in.readLine()) != null){
            if(str.indexOf(' ') != expectedSpacePos || str.isEmpty()){
                throw new IOException("Alphabet file has wrong format");
            }
            map.put(str.charAt(0), str.split(" ")[1]);
        }

        in.close();

        if(map.isEmpty()) {
            throw new IOException("Alphabet file is empty, nothing to do there");
        }
    }

    public String getMorseCodeByChar(Character character) {
        return map.get(character);
    }

    public Character getCharByMorseCode(String code) {
        for(Character key : map.keySet()) {
            if (map.get(key).equals(code)) {
                return key;
            }
        }
        return null;
    }
}
