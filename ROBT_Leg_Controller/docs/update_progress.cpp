#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <cmath>

int count_matches(const std::string& text, const std::regex& re) {
    return std::distance(
        std::sregex_iterator(text.begin(), text.end(), re),
        std::sregex_iterator()
    );
}

std::string make_bar(int complete, int in_progress, int not_started, int total_bars = 30) {
    int total = complete + in_progress + not_started;
    int c = std::round((double)complete / total * total_bars);
    int i = std::round((double)in_progress / total * total_bars);
    int n = total_bars - c - i;
    return std::string(c, '🟩') + std::string(i, '🟨') + std::string(n, '⬜');
}

std::string percent(int part, int total) {
    return std::to_string((int)std::round(100.0 * part / total));
}

int main() {
    std::ifstream in("Goals_And_Steps.md");
    if (!in) {
        std::cerr << "Could not open Goals_And_Steps.md\n";
        return 1;
    }
    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    // Extract Goals and Next Steps sections
    std::smatch match;
    std::regex goals_re("## Goals([\\s\\S]+?)(?=##|$)");
    std::regex next_re("## Next Steps([\\s\\S]+?)(?=##|$)");
    std::string goals, next_steps;
    if (std::regex_search(content, match, goals_re)) goals = match[1];
    if (std::regex_search(content, match, next_re)) next_steps = match[1];

    std::regex re_x("- \\[x\\]");
    std::regex re_ip("- \\[(⏳|😰|🧩|🚩)\\]");
    std::regex re_n("- \\[ \\]");

    int g_c = count_matches(goals, re_x);
    int g_i = count_matches(goals, re_ip);
    int g_n = count_matches(goals, re_n);

    int n_c = count_matches(next_steps, re_x);
    int n_i = count_matches(next_steps, re_ip);
    int n_n = count_matches(next_steps, re_n);

    int t_c = g_c + n_c, t_i = g_i + n_i, t_n = g_n + n_n;
    int g_total = g_c + g_i + g_n;
    int n_total = n_c + n_i + n_n;
    int t_total = t_c + t_i + t_n;

    std::string goals_bar = make_bar(g_c, g_i, g_n);
    std::string next_bar = make_bar(n_c, n_i, n_n);
    std::string total_bar = make_bar(t_c, t_i, t_n);

    std::string goals_stats = "Complete: " + percent(g_c, g_total) + "% | In Progress: " + percent(g_i, g_total) + "% | Not Started: " + percent(g_n, g_total) + "%";
    std::string next_stats = "Complete: " + percent(n_c, n_total) + "% | In Progress: " + percent(n_i, n_total) + "% | Not Started: " + percent(n_n, n_total) + "%";
    std::string total_stats = "Complete: " + percent(t_c, t_total) + "% | In Progress: " + percent(t_i, t_total) + "% | Not Started: " + percent(t_n, t_total) + "%";

    // Replace the progress bars and stats in the file
    std::regex total_re(R"((\*\*Total Progress:\*\*\s*\n)[^\n]*\n[^\n]*\n)");
    std::regex goals_rebar(R"((\*\*Goals Progress:\*\*\s*\n)[^\n]*\n[^\n]*\n)");
    std::regex next_rebar(R"((\*\*Next Steps Progress:\*\*\s*\n)[^\n]*\n[^\n]*\n)");

    content = std::regex_replace(content, total_re, "$1" + total_bar + "  \n" + total_stats + "\n");
    content = std::regex_replace(content, goals_rebar, "$1" + goals_bar + "  \n" + goals_stats + "\n");
    content = std::regex_replace(content, next_rebar, "$1" + next_bar + "  \n" + next_stats + "\n");

    std::ofstream out("Goals_And_Steps.md");
    out << content;
    out.close();

    std::cout << "Progress bars and stats updated!\n";
    return 0;
}