const BASE_URL = "http://localhost:18080";

let isShowing = false;

/* ---------- ASYNC SLEEP ---------- */
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

/* ---------- SHOW OUTPUT FOR 5 SECONDS (NO TIMERS) ---------- */
async function showOutput(text) {
    // Prevent overlapping calls
    if (isShowing) return;
    isShowing = true;

    const output = document.getElementById("output");

    // Show message
    output.textContent = text;

    // Hold message for 5 seconds
    await sleep(5000);

    // Reset message
    output.textContent = "Ready for next operation...";
    isShowing = false;
}

/* ---------- HELPER FUNCTION ---------- */
async function postData(url, params) {
    try {
        const response = await fetch(url, {
            method: "POST",
            body: params,
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            }
        });
        return await response.text();
    } catch {
        return "ERROR: Could not reach server";
    }
}

/* ---------- ADD EMPLOYEE ---------- */
async function addEmployee() {
    const params = new URLSearchParams();
    params.append("id", empId.value);
    params.append("name", empName.value);
    params.append("salary", salary.value);

    const result = await postData(`${BASE_URL}/add`, params);
    await showOutput(result);
}

/* ---------- UPDATE EMPLOYEE ---------- */
async function updateEmployee() {
    const params = new URLSearchParams();
    params.append("id", empId.value);
    params.append("name", empName.value);
    params.append("salary", salary.value);

    const result = await postData(`${BASE_URL}/update`, params);
    await showOutput(result);
}

/* ---------- DELETE EMPLOYEE ---------- */
async function deleteEmployee() {
    const params = new URLSearchParams();
    params.append("id", deleteId.value);

    const result = await postData(`${BASE_URL}/delete`, params);
    await showOutput(result);
}

/* ---------- SEARCH EMPLOYEE ---------- */
async function searchEmployee() {
    try {
        const response = await fetch(`${BASE_URL}/search?id=${searchId.value}`);
        const result = await response.text();
        await showOutput(result);
    } catch {
        await showOutput("ERROR: Could not reach server");
    }
}

/* ---------- SALARY SLIP ---------- */
async function salarySlip() {
    try {
        const response = await fetch(`${BASE_URL}/salary?id=${searchId.value}`);
        const result = await response.text();
        await showOutput(result);
    } catch {
        await showOutput("ERROR: Could not reach server");
    }
}
