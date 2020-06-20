import java.util.*;

public class Brace_Expansion_II {
    public static void main(String[] args) {
        Solution s = new Solution();
        System.out.println("Result: " + s.braceExpansionII("{{a,z},a{b,c},{ab,z}}"));
    }
}

/**
 * 1. Use ListIterator saves runtime
 * 2. Most solution uses top-level comma-split method:
 *      Split based on comma (with lowest precedence) and then parse each chunk
 */

class Solution {
    public List<String> braceExpansionII(String expression) {
        List<String> result = evaluateExpr('{' + expression + '}', 0, expression.length()+1);

        // Sort and remove duplicates
        Collections.sort(result);

        // Remove duplicates
        ListIterator<String> iter = result.listIterator();
        String lastS = "X", currS;
        while(iter.hasNext()) {
            if((currS = iter.next()).equals(lastS)) iter.remove();
            lastS = currS;
        }

        return result;
    }
    
    private List<String> evaluateExpr(String subExp, int start, int end) {
        int idx = start+1;

        int lastBrac = -1;

        List<List<String>> exprs = new LinkedList<>();

        List<String> subExprs;

        int nestedCount = 0;

        while(idx < end) {
            char c = subExp.charAt(idx);
            // A nested sub expression
            if(subExp.charAt(idx) == '{') {
                if(nestedCount++ == 0) lastBrac = idx;
            } else if(subExp.charAt(idx) == '}') {
                if(--nestedCount == 0) {
                    subExprs = evaluateExpr(subExp, lastBrac, idx);
                    if(subExprs != null) exprs.add(subExprs);
                }
            } else if(nestedCount == 0) {
                subExprs = new LinkedList<>();
                subExprs.add("" + c);
                exprs.add(subExprs);
            }
            idx++;
        }

        // Edge case expr is empty
        if(exprs.isEmpty()) return null;

        // Combine strings
        List<String> result = new LinkedList<>(), concatList = new LinkedList<>();
        List<String> currList;
        for(int i = 0; i < exprs.size(); i++) {
            currList = exprs.get(i);
            // System.out.println("Curr: " + currList + " R" + result);
            if(currList.get(0).equals(",")) {
                result.addAll(concatList);
                concatList.clear();
            } else {
                if(concatList.isEmpty()) concatList.addAll(currList);
                else {
                    // Concat every string since last comma
                    LinkedList<String> tempList = new LinkedList<>();
                    for(String s: concatList) {
                        for(String t: currList) {
                            tempList.add(s + t);
                        }
                    }

                    concatList = tempList;
                }
            }
        }

        result.addAll(concatList);

        return result;
    }
}