import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class PartC {
  public static void main(String[] args) throws Exception {
      Path dir = Paths.get("/Users/matthewlee/projects/UNO_4401_OS/os-assign3");
      long startTime = System.currentTimeMillis();

      try (var stream = Files.newDirectoryStream(dir, "*.{txt,csv}")) {
          for (Path entry : stream) {
              findMostFrequentWord(entry.toFile());
          }
      }

      long endTime = System.currentTimeMillis();
      System.out.println("Total time: " + (endTime - startTime) + " ms");
  }

  private static void findMostFrequentWord(File file) throws Exception {
      FileReader fr = new FileReader(file);
      BufferedReader br = new BufferedReader(fr);

      HashMap<String, Integer> wordFrequencyMap = new HashMap<>();
      Pattern pattern = Pattern.compile("\\b\\w{7,}\\b", Pattern.CASE_INSENSITIVE);

      String line;
      while ((line = br.readLine()) != null) {
          Matcher matcher = pattern.matcher(line);
          while (matcher.find()) {
              String word = matcher.group().toLowerCase();
              wordFrequencyMap.put(word, wordFrequencyMap.getOrDefault(word, 0) + 1);
          }
      }

      String mostFrequentWord = "";
      int maxFrequency = 0;
      for (Map.Entry<String, Integer> entry : wordFrequencyMap.entrySet()) {
          if (entry.getValue() > maxFrequency) {
              mostFrequentWord = entry.getKey();
              maxFrequency = entry.getValue();
          }
      }

      System.out.println(file.getName() + ": " + mostFrequentWord);
  }
}
