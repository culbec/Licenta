import communication.Communication;
import encoder.CircularEncoding;
import encoder.NaiveEncoding;

import java.util.*;

public class Main {

    // Theta(L1.size() + L2.size()) = Theta(n + m)
    static List<String> mergeMessagesRec(List<String> L1, int indexL1, List<String> L2, int indexL2) {
        if (indexL1 >= L1.size() && indexL2 >= L2.size()) {
            return new ArrayList<>();
        } else if (indexL1 < L1.size() && indexL2 >= L2.size()) {
            List<String> result = mergeMessagesRec(L1, indexL1 + 1, L2, indexL2);
            result.add(0, L1.get(indexL1));
            return result;
        } else if (indexL1 >= L1.size() && indexL2 < L2.size()) {
            List<String> result = mergeMessagesRec(L1, indexL1, L2, indexL2 + 1);
            result.add(0, L2.get(indexL2));
            return result;
        }

        if (L1.get(indexL1).compareTo(L2.get(indexL2)) < 0) {
            List<String> result = mergeMessagesRec(L1, indexL1 + 1, L2, indexL2);
            result.add(0, L1.get(indexL1));
            return result;
        }
        List<String> result = mergeMessagesRec(L1, indexL1, L2, indexL2 + 1);
        result.add(0, L2.get(indexL2));
        return result;
    }

    static List<String> mergeMessages(List<String> L1, List<String> L2) {
        return mergeMessagesRec(L1, 0, L2, 0);
    }

    static boolean isCircularPermutation(String m1, String m2) {
        if (m1.length() != m2.length()) {
            return false;
        }

        if (m1.equals(m2)) {
            return true;
        }

        int mLength = m1.length();
        for (int i = 1; i < mLength; i++) {
            boolean ok = true;

            for (int j = 0; j < mLength && ok; j++) {
                if (m1.charAt((j + i) % mLength) != m2.charAt(j)) {
                    ok = false;
                }
            }

            if (ok) {
                return true;
            }
        }

        return false;
    }

    // Search in a hash table AVERAGE time complexity: O(1) amortized
    // All encoded messages iteration: Theta(n)
    // ==> Theta(n) + O(1) = Theta(1) average time complexity (amortized)
    static int getUniqueEncodedMessagesNumber(Communication c) {
        Map<String, Boolean> messagesMap = new HashMap<>();

        c.getEncodedMessages().forEach(message -> {
            if (!messagesMap.containsKey(message)) {
                messagesMap.put(message, true);
            }
        });

        return messagesMap.size();
    }

    public static void main(String[] args) {
        List<String> L1 = Arrays.asList("1", "4", "9");
        List<String> L2 = Arrays.asList("0", "3", "7");

        List<String> L = mergeMessages(L1, L2);
        L.forEach(message -> System.out.printf("%s ", message));
        System.out.println();

        String m1 = "ENCODER";
        String m2 = "CODEREN";
        System.out.println(isCircularPermutation(m1, m2));

        Communication o1 = new Communication(new CircularEncoding(10));
        Communication o2 = new Communication(new NaiveEncoding());

        o1.addMessage("bar"); o2.addMessage("bar");
        o1.addMessage("cod"); o2.addMessage("cod");
        o1.addMessage("apt"); o2.addMessage("apt");

        List<String> o1O2Merged = mergeMessages(o1.getEncodedMessages(), o2.getEncodedMessages());
        o1O2Merged.forEach(message -> System.out.printf("%s ", message));
        System.out.println();
    }
}
