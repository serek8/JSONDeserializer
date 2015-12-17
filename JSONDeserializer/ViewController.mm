//
//  ViewController.m
//  test
//
//  Created by Jan Seredynski on 04/11/15.
//  Copyright © 2015 Jan Seredynski. All rights reserved.
//

#import "ViewController.h"
#import <security/security.h>
#include "Parser.hpp"
#include "ProfitParser.hpp"
#include "User.hpp"


@interface ViewController ()
{
    User user;
}

@property (weak, nonatomic) IBOutlet UITextView *inputSourceTextField;
@property (weak, nonatomic) IBOutlet UILabel *labelA;

@property (weak, nonatomic) IBOutlet UIButton *parseButton;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}



- (IBAction)parse:(UIButton *)sender {
    try{
        
        
        Parser parser([self.inputSourceTextField.text UTF8String]);
        
        Profits profit((ProfitParser(parser)));
        
        [self.labelA setText:[NSString stringWithFormat:@"a=%d \nb=%f\nc=%d \nd: %s\nmy_plug_ins_[0]:%s\nmy_plug_ins_[1]: %s\n...You can test all the values in the debuger mode", profit.a_,
                              profit.b_,
                              profit.c_,
                              profit.d_.c_str(),
                              profit.my_plug_ins_[0].c_str(),
                              profit.my_plug_ins_[1].c_str()]];

    }catch(std::runtime_error e)
    {
        NSLog(@"Parsing Error, description: %s", e.what());
    }
    
    
}





@end
