
package ComputeRevenue_cpp;
use strict; use Cwd 'realpath';  use File::Basename;  use lib dirname(__FILE__);  use SPL::Operator::Instance::OperatorInstance; use SPL::Operator::Instance::Annotation; use SPL::Operator::Instance::Context; use SPL::Operator::Instance::Expression; use SPL::Operator::Instance::ExpressionTree; use SPL::Operator::Instance::ExpressionTreeEvaluator; use SPL::Operator::Instance::ExpressionTreeVisitor; use SPL::Operator::Instance::ExpressionTreeCppGenVisitor; use SPL::Operator::Instance::InputAttribute; use SPL::Operator::Instance::InputPort; use SPL::Operator::Instance::OutputAttribute; use SPL::Operator::Instance::OutputPort; use SPL::Operator::Instance::Parameter; use SPL::Operator::Instance::StateVariable; use SPL::Operator::Instance::TupleValue; use SPL::Operator::Instance::Window; 
sub main::generate($$) {
   my ($xml, $signature) = @_;  
   print "// $$signature\n";
   my $model = SPL::Operator::Instance::OperatorInstance->new($$xml);
   unshift @INC, dirname ($model->getContext()->getOperatorDirectory()) . "/../impl/nl/include";
   $SPL::CodeGenHelper::verboseMode = $model->getContext()->isVerboseModeOn();
   print '/* Additional includes go here */', "\n";
   print "\n";
   SPL::CodeGen::implementationPrologue($model);
   print "\n";
   print "\n";
   print '#include <fstream>', "\n";
   print "\n";
   print 'using namespace std;', "\n";
   print "\n";
   print '// Constructor', "\n";
   print 'MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()', "\n";
   print '{', "\n";
   print '    // Initialization code goes here', "\n";
   print '}', "\n";
   print "\n";
   print '// Destructor', "\n";
   print 'MY_OPERATOR_SCOPE::MY_OPERATOR::~MY_OPERATOR() ', "\n";
   print '{', "\n";
   print '    // Finalization code goes here', "\n";
   print '}', "\n";
   print "\n";
   print '// Notify port readiness', "\n";
   print 'void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady() ', "\n";
   print '{', "\n";
   print '    // Notifies that all ports are ready. No tuples should be submitted before', "\n";
   print '    // this. Source operators can use this method to spawn threads.', "\n";
   print "\n";
   print '    /*', "\n";
   print '      createThreads(1); // Create source thread', "\n";
   print '    */', "\n";
   print '}', "\n";
   print ' ', "\n";
   print '// Notify pending shutdown', "\n";
   print 'void MY_OPERATOR_SCOPE::MY_OPERATOR::prepareToShutdown() ', "\n";
   print '{', "\n";
   print '    // This is an asynchronous call', "\n";
   print '}', "\n";
   print "\n";
   print '// Processing for source and threaded operators   ', "\n";
   print 'void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t idx)', "\n";
   print '{', "\n";
   print '    // A typical implementation will loop until shutdown', "\n";
   print '    /*', "\n";
   print '      while(!getPE().getShutdownRequested()) {', "\n";
   print '          // do work ...', "\n";
   print '      }', "\n";
   print '    */', "\n";
   print '}', "\n";
   print "\n";
   print '// Tuple processing for mutating ports ', "\n";
   print 'void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple & tuple, uint32_t port)', "\n";
   print '{', "\n";
   print '    // Sample submit code', "\n";
   print '    /* ', "\n";
   print '      submit(otuple, 0); // submit to output port 0', "\n";
   print '    */', "\n";
   print '	', "\n";
   print '	int32 strategy = tuple.getAttributeValue("strategy");', "\n";
   print '	float64 price = tuple.getAttributeValue("price");', "\n";
   print '	', "\n";
   print '	ifstream ifs("purchaseHistory.txt");', "\n";
   print '	', "\n";
   print '	int32 holding;', "\n";
   print '	ifs>>holding;', "\n";
   print '	', "\n";
   print '	float64 buy_price;', "\n";
   print '	ifs>>buy_price;', "\n";
   print '	', "\n";
   print '	ifs.close();', "\n";
   print '	', "\n";
   print '	if(holding == -1) {', "\n";
   print '		if(strategy == -1) {', "\n";
   print '			return;', "\n";
   print '		}', "\n";
   print '		', "\n";
   print '		holding = 1;', "\n";
   print '		ofstream ofs("purchaseHistory.txt");', "\n";
   print '		ofs<<holding<<" "<<price;', "\n";
   print '	}', "\n";
   print '	', "\n";
   print '	if(strategy == 1) {', "\n";
   print '		return;', "\n";
   print '	}', "\n";
   print '	', "\n";
   print '	holding = -1;', "\n";
   print '	ofstream ofs("purchaseHistory.txt");', "\n";
   print '	ofs<<holding<<" "<<price;', "\n";
   print '	', "\n";
   print '	float64 revenue = price - buy_price;', "\n";
   print '	', "\n";
   print '	OPort0Type otuple;', "\n";
   print '	otuple.assignFrom(tuple, false);', "\n";
   print '	', "\n";
   print '	ValueHandle handle0 = otuple.getAttributeValue("revenue");', "\n";
   print '	float64& r = handle0;', "\n";
   print '	r = revenue;', "\n";
   print '	', "\n";
   print '	submit(otuple, 0);', "\n";
   print '}', "\n";
   print "\n";
   print '// Tuple processing for non-mutating ports', "\n";
   print 'void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple const & tuple, uint32_t port)', "\n";
   print '{', "\n";
   print '    // Sample submit code', "\n";
   print '    /* ', "\n";
   print '      OPort0Type otuple;', "\n";
   print '      submit(otuple, 0); // submit to output port 0', "\n";
   print '    */', "\n";
   print '}', "\n";
   print "\n";
   print '// Punctuation processing', "\n";
   print 'void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Punctuation const & punct, uint32_t port)', "\n";
   print '{', "\n";
   print '    /*', "\n";
   print '      if(punct==Punctuation::WindowMarker) {', "\n";
   print '        // ...;', "\n";
   print '      } else if(punct==Punctuation::FinalMarker) {', "\n";
   print '        // ...;', "\n";
   print '      }', "\n";
   print '    */', "\n";
   print '}', "\n";
   print "\n";
   SPL::CodeGen::implementationEpilogue($model);
   print "\n";
   print "\n";
   CORE::exit $SPL::CodeGen::USER_ERROR if ($SPL::CodeGen::sawError);
}
1;