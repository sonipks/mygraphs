// Used for Orthogonal Cluster Layout
#include <ogdf/packing/TileToRowsCCPacker.h>
#include <ogdf/cluster/ClusterOrthoLayout.h>
#include <ogdf/cluster/ClusterPlanarizationLayout.h>

// Used for random graph generator methods
#include <ogdf/basic/graph_generators.h>

// Used for creating output file
#include <ogdf/fileformats/GraphIO.h>
using namespace ogdf;

int main(int argc, char* argv[])
{

	//--------------------------------------------------------------------
	//(1) Create Graph, Cluster Graph and Cluster Graph Attrobutes.
	Graph G; 


	randomSimpleGraph(G, 10, 10); // grapth genarate. nodes,edges
	ClusterGraph CG( G );

	//last argument is the max number of clusters can be formed
	randomClusterPlanarGraph(CG,G,50);	 

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

	GraphIO::writeGML( CGA,"Cluster_Orthogonal.gml" );
	GraphIO::drawSVG(CGA, "e:\\Cluster_Orthogonal.svg");

	return 0;
}
