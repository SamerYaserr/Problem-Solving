// zero indexed
vector<int> nextSmaller(vector<int>& v) {
    int n = v.size();
    vector<int> ans(n, n), st;
    for (int i = 0; i < n; ++i) {
        while ( not st.empty() and v[st.back()] > v[i] ) {
            ans[st.back()] = i, st.pop_back();
        }
        st.push_back(i);
    }
    return ans;
}

vector<int> previousSmaller(vector<int>& v) {
    int n = v.size();
    vector<int> ans(n, -1), st;
    for (int i = n - 1; i >= 0; --i) {
        while ( not st.empty() and v[st.back()] > v[i] ) {
            ans[st.back()] = i, st.pop_back();
        }
        st.push_back(i);
    }
    return ans;
}

vector<int> nextGreater(vector<int>& v) {
    int n = v.size();
    vector<int> ans(n, n), st;
    for (int i = 0; i < n; ++i) {
        while ( not st.empty() and v[st.back()] < v[i] ) {
            ans[st.back()] = i, st.pop_back();
        }
        st.push_back(i);
    }
    return ans;
}

vector<int> previousGreater(vector<int>& v) {
    int n = v.size();
    vector<int> ans(n, -1), st;
    for (int i = n - 1; i >= 0; --i) {
        while ( not st.empty() and v[st.back()] < v[i] ) {
            ans[st.back()] = i, st.pop_back();
        }
        st.push_back(i);
    }
    return ans;
}