from http.server import BaseHTTPRequestHandler, HTTPServer
from random import randrange

def get_dist_fake():
  return randrange(0, 100)

class RequestHandler(BaseHTTPRequestHandler):
  def do_GET(self):
    self.send_response(200)
    self.send_header("Content-Type", "text/plain")
    self.send_header("Access-Control-Allow-Origin", "*")
    self.send_header("Access-Control-Allow-Methods", "*")
    self.send_header("Access-Control-Allow-Headers", "*")
    self.end_headers()
    dist = get_dist_fake()
    self.wfile.write(bytes(f"{dist}", "utf8"))

if __name__ == "__main__":
  host = "localhost"
  port = 8081
  server = HTTPServer((host, port), RequestHandler)
  try:
    print(f"Listening on http://{host}:{port}")
    server.serve_forever()
  except KeyboardInterrupt:
    pass
  server.server_close()
