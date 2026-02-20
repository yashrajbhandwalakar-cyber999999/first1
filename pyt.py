from flask import Flask, request

app = Flask(__name__)

@app.route("/", methods=["GET"])
def home():
    cnt = request.args.get("cnt", type=int)
    
    html = """
    <html>
    <head>
    <title>Adjacency Matrix</title>
    </head>
    <body>
    <h2>Adjacency Matrix Generator</h2>
    """

    if cnt:
        html += f"""
        <form method="get">
        <input type="hidden" name="cnt" value="{cnt}">
        """
        k = 1
        total = (cnt*(cnt-1)//2)+cnt
        for i in range(total):
            html += f"""
            TO: <input type="text" name="num{k}"> 
            FROM: <input type="text" name="num{k+1}"><br>
            """
            k += 2

        html += """
        <input type="submit" value="Submit">
        </form>
        """

        # Values read करणे
        values = []
        for key in request.args:
            if key.startswith("num"):
                val = request.args.get(key, type=int)
                if val is not None:
                    values.append(val)

        # Matrix तयार करणे
        arr = [[0]*cnt for _ in range(cnt)]

        for i in range(0, len(values), 2):
            if i+1 < len(values):
                a = values[i]
                b = values[i+1]
                if a < cnt and b < cnt:
                    arr[a][b] = 1
                    arr[b][a] = 1

        # Matrix print
        html += "<pre>\n    "
        for i in range(cnt):
            html += f" v{i}"
        html += "\n"

        for i in range(cnt):
            html += f"v{i} "
            for j in range(cnt):
                html += f"  {arr[i][j]}"
            html += "\n"
        html += "</pre>"

        # Degree
        html += "<h3>Edges Degree</h3>"
        for i in range(cnt):
            deg = sum(arr[i])
            html += f"<p>v{i} = {deg} DEGREE</p>"

    html += "</body></html>"
    return html


if __name__ == "__main__":
    app.run(debug=True)