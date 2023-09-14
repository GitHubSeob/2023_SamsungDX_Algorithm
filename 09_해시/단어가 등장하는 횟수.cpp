#include <iostream>
#include <string>
#define ll long long
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int idx(0), answer(0);
		string book("");
		string word("");
		cin >> book >> word;
		ll book_val(0), word_val(0);
		ll power(1);
		if (book.size() >= word.size()) {
			for (int idx = 0; idx <= book.size() - word.size(); ++idx) {
				if (idx == 0) {
					for (int w_idx = 0; w_idx < word.size(); ++w_idx) {
						book_val += (book[word.size() - w_idx - 1] * power);
						word_val += (word[word.size() - w_idx - 1] * power);
						if (w_idx < word.size() - 1) {
							power = power * 95;
						}

					}
				}
				else {
					book_val = (95 * (book_val - book[idx - 1] * power));
					book_val += book[idx + word.size() - 1];
				}

				if (book_val == word_val) {
					++answer;
				}
			}
		}

		cout << "#" << test_case << " " << answer << '\n';
	}
}