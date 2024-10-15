from concurrent import futures
import logging

from sentence_transformers import SentenceTransformer
import numpy as np

import grpc
import par2vec_pb2
import par2vec_pb2_grpc

class Par2VecServicer(par2vec_pb2_grpc.Par2VecServicer):
    def __init__(self):
        self.model = SentenceTransformer('paraphrase-MiniLM-L6-v2')
        logging.info("Initialization in Par2VecServicer...done")

    def hello(self, request, context):
        temp = request.hello
        temp += "Hi," + temp
        logging.info(temp)
        return par2vec_pb2.HelloReply(reply=temp)
    
    def convertParToVec(self, request, context):
        embeddings = self.model.encode(request.paragraph)
        #logging.info(type(embeddings))
        #logging.info(len(embeddings))
        #logging.info(type(embeddings.tolist()))
        #logging.info(embeddings.tolist())
        if isinstance(embeddings, np.ndarray):
            reply = par2vec_pb2.DefaultReply(
                dim=len(embeddings),
                fVec=embeddings.tolist()
            )
            return reply
        logging.error("Error, the embedding vector is not ndarray!")
        return par2vec_pb2.DefaultReply(dim=0, fVec=[])    
    
def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=3))
    par2vec_pb2_grpc.add_Par2VecServicer_to_server(Par2VecServicer(), server)
    server.add_insecure_port("[::]:50052")
    server.start()
    server.wait_for_termination()
    print("Listening :50052...")

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    serve()