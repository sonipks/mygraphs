// Used for Orthogonal Cluster Layout
#include <ogdf/packing/TileToRowsCCPacker.h>
#include <ogdf/cluster/ClusterOrthoLayout.h>
#include <ogdf/cluster/ClusterPlanarizationLayout.h>
// Used for creating output file
#include <ogdf/fileformats/GraphIO.h>
using namespace ogdf;

int main(int argc, char* argv[])
{
	//--------------------------------------------------------------------
	//(1) Create Graph, Cluster Graph and Cluster Graph Attrobutes.
	Graph G;

	//randomSimpleGraph(G, 10, 10); // grapth genarate. nodes,edges
	//node l11 = G.newNode();
	//node l12 = G.newNode();
	//G.newEdge(l11,l12);
	int n=10;
	node l[10];
	// Array<node> v(10);
	for(int i = 0; i < n; i++)
		l[i] = G.newNode();
	G.newEdge(l[0],l[1]);
	G.newEdge(l[0],l[2]);
	G.newEdge(l[0],l[3]);
	G.newEdge(l[0],l[4]);
	G.newEdge(l[0],l[5]);

	ClusterGraph CG( G );

	//last argument is the max number of clusters can be formed
	//randomClusterPlanarGraph(CG,G,7);
	cluster c1 = CG.newCluster(CG.clusterOf(l[1]));
	CG.reassignNode(l[0],c1);
	cluster c2 = CG.newCluster(CG.clusterOf(l[3]));
	CG.reassignNode(l[1],c2);
	CG.reassignNode(l[6],c2);
	CG.reassignNode(l[7],c2);
	CG.reassignNode(l[8],c2);
	CG.reassignNode(l[9],c2);
	cluster c3 = CG.newCluster(CG.clusterOf(l[1]));
	CG.reassignNode(l[2],c3);
	CG.reassignNode(l[3],c3);
	CG.reassignNode(l[4],c3);
	CG.reassignNode(l[5],c3);
	ClusterGraphAttributes CGA( CG,
		GraphAttributes::nodeGraphics |
		GraphAttributes::edgeGraphics |
		GraphAttributes::nodeLabel |
		GraphAttributes::edgeStyle |
		GraphAttributes::nodeStyle |
		GraphAttributes::nodeTemplate);
	node v;
	forall_nodes( v, G ){ // iterate through all the node in the graph
		CGA.fillColor( v ) = Color( "#FFFF00" ); // set node color to yellow
		CGA.height( v ) = 20.0; // set the height to 20.0
		CGA.width( v ) = 20.0; // set the width to 40.0
		CGA.shape(v) = ogdf::Shape::shEllipse;
		string s = to_string(v->index());
		char const *pchar = s.c_str(); //use char const* as target type
		CGA.label( v ) = pchar;
	}
	edge e;
	forall_edges(e ,G) // set default edge color and type
	{
		CGA.bends(e);
		//CGA.arrowType(e) = ogdf::EdgeArrow::;
		CGA.strokeColor(e) = Color("#0000FF");
	}
	// (7) Orthogonal Cluster Layout
	ClusterPlanarizationLayout PL;
	ClusterOrthoLayout* pClusterOrthoLayout = new ClusterOrthoLayout;
	pClusterOrthoLayout->separation( 20.0f );
	PL.setPlanarLayouter( pClusterOrthoLayout );
	PL.setPacker( new TileToRowsCCPacker );
	PL.ClusterPlanarizationLayout::call(G, CGA,CG);
	//GraphIO::writeGML( CGA,"Cluster_Orthogonal.gml" );
	GraphIO::drawSVG(CGA, "e:\\Cluster_Orthogonal2.svg");
	return 0;
}
