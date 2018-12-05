import argparse
import pygraphviz as pgv
bblocksset = set([])
bblocks = {}
functions = set([])

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Generating dynamic dependence graph')
	parser.add_argument('-graph', type=str, required=True,  help='Graph File')
	parser.add_argument('-dynamic', type=str, required=True,  help='Dynamic File')
	parser.add_argument('-save', type=str, required=True,  help='Dynamic File')
	args = parser.parse_args()
	dynamicfile = args.dynamic
	graphfile = args.graph
	savename = args.save

	# Read the basic block file
	with open(dynamicfile) as file: 
		data = file.readline()
		while data:
			data = data.strip()
			datalist = data.split("/")
			functions.add(datalist[0])
			bblocksset.add(data)
			if(data in bblocks):
				bblocks[data] += 1
			else:
				bblocks[data] = 1

			data = file.readline()

	# Read the graphviz file
	sdg = pgv.AGraph(graphfile)

	# Remove basicblocks which are not executed
	allfunctions = sdg.subgraphs()
	for i in range(len(allfunctions)):
		function = allfunctions[i]
		funcname = function.node_attr['label'].split()[1]
		if(funcname in functions):
			allbasicblocks = function.subgraphs()
			for j in range(len(allbasicblocks)):
				basicblock = allbasicblocks[j]
				bbname = basicblock.node_attr["label"].split()[1]
				if(funcname+"/"+bbname not in bblocksset):
					allnodes = basicblock.nodes()
					inedges = sdg.in_edges(allnodes)
					outedges = sdg.out_edges(allnodes)
					edges = inedges + outedges
					sdg.delete_edges_from(list(set(edges)))
					sdg.delete_nodes_from(allnodes)

					print("Removed basicblock: "+funcname+"/"+bbname)

		else:
			allnodes = function.nodes()
			inedges = sdg.in_edges(allnodes)
			outedges = sdg.out_edges(allnodes)
			edges = inedges + outedges
			sdg.delete_edges_from(list(set(edges)))
			sdg.delete_nodes_from(allnodes)
			print("Removed function: "+funcname)
	
	# Remove Edge Dependencies which are not used
	edges = sdg.edges()
	for i in range(len(edges)):
		edge = edges[i]
		if(edge[0] == edge[1]):

			allfunctions = sdg.subgraphs()
			for i in range(len(allfunctions)):
				function = allfunctions[i]
				allbasicblocks = function.subgraphs()
				for j in range(len(allbasicblocks)):
					basicblock = allbasicblocks[j]
					bbname = basicblock.node_attr["label"].split()[1]
					if(basicblock.has_node(edge[0])):
						if(bblocks[bbname] <= 1):
							sdg.delete_edge(edge[0],edge[1])
							print("Removed Edge: "+bbname+"->"+bbname)

	sdg.write(savename)
	sdg.close()